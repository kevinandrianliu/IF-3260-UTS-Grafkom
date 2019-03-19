#include <cerrno>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include <thread>
#include <cstring>
#include <ctime>
#include <mutex>
#include "util/func_util.h"
#include "objects.h"
#include "objects_util.h"

using namespace std;

char menu_bar_option_selection = -1;
char menu_bar_selection = 0;
int key_code = 0x00;
bool refresh_screen = false;
bool accessing_menu_bar = false;
bool out = false;

void userInput(int fd){
    ssize_t n;
    struct input_event ev;

    while(1){
        n = read(fd, &ev, sizeof ev);
        if (n == (ssize_t)-1){
            if (errno == EINTR){
                continue;
            } else {
                break;
            }
        } else if (n != sizeof ev){
            errno = EIO;
            break;
        }

        if (ev.type == EV_KEY && ev.value == 1){
            switch (ev.code){
                case(105):  // KEY_LEFT
                    if (accessing_menu_bar){
                        if (menu_bar_selection > 0){
                            menu_bar_selection--;
                        }
                        menu_bar_option_selection = -1;
                        refresh_screen = true;
                    }
                    break;
                case(106):  // KEY_RIGHT
                    if (accessing_menu_bar){
                        if (menu_bar_selection < 3){
                            menu_bar_selection++;
                        }
                        menu_bar_option_selection = -1;
                        refresh_screen = true;
                    }
                    break;
                case(103):  // KEY_UP
                    if (accessing_menu_bar){
                        if (menu_bar_option_selection >= 0){
                            menu_bar_option_selection--;
                        }
                        refresh_screen = true;
                    }
                    break;
                case(108):  // KEY_DOWN
                    if (accessing_menu_bar){
                        menu_bar_option_selection++;
                        refresh_screen = true;
                    }
                    break;
                case(1):    // KEY_ESC
                    out = true;
                    break;
                case(KEY_RIGHTALT):
                case(KEY_LEFTALT):
                    accessing_menu_bar = !accessing_menu_bar;
                    menu_bar_selection = 0;
                    menu_bar_option_selection = -1;
                    refresh_screen = true;
                    break;
                default:
                    break;
            }

            key_code = ev.code;
        }

        if (out){
            break;
        }
    }
}

void drawMenuBar(WINDOW** menu_bar_options_window,WINDOW * menu_bar_window){  
    char ** menu_bar_options;
    int menu_bar_options_size;

    switch(menu_bar_selection){
        case(0):
            menu_bar_options_size = 4;
            menu_bar_options = (char**) malloc (4 * sizeof (char *));
            menu_bar_options[0] = "New";
            menu_bar_options[1] = "Open";
            menu_bar_options[2] = "Save";
            menu_bar_options[3] = "Exit";
            break;
        case(1):
            menu_bar_options_size = 6;
            menu_bar_options = (char**) malloc (6 * sizeof (char *));
            menu_bar_options[0] = "Zoom in";
            menu_bar_options[1] = "Zoom out";
            menu_bar_options[2] = "Pan left";
            menu_bar_options[3] = "Pan right";
            menu_bar_options[4] = "Pan top";
            menu_bar_options[5] = "Pan bottom";
            break;
        case(2):
            menu_bar_options_size = 3;
            menu_bar_options = (char**) malloc (3 * sizeof (char *));
            menu_bar_options[0] = "Color";
            menu_bar_options[1] = "Line thickness";
            menu_bar_options[2] = "Line style";
            break;
        case(3):
            menu_bar_options_size = 4;
            menu_bar_options = (char**) malloc (4 * sizeof (char *));
            menu_bar_options[0] = "Add line";
            menu_bar_options[1] = "Add polygon";
            menu_bar_options[2] = "Select";
            menu_bar_options[3] = "Delete";
            break;
        default:
            break;
    }
    
    if (menu_bar_option_selection >= menu_bar_options_size){
        menu_bar_option_selection = menu_bar_options_size - 1;
    }

    refresh();

    wbkgd(menu_bar_window, COLOR_PAIR(1));
    if (menu_bar_selection == 0 && accessing_menu_bar){
        wattron(menu_bar_window,COLOR_PAIR(2));
    }
    mvwprintw(menu_bar_window,0,1,"File");
    wattroff(menu_bar_window,COLOR_PAIR(2));
    if (menu_bar_selection == 1 && accessing_menu_bar){
        wattron(menu_bar_window,COLOR_PAIR(2));
    }
    mvwprintw(menu_bar_window,0,9,"View");
    wattroff(menu_bar_window,COLOR_PAIR(2));
    if (menu_bar_selection == 2 && accessing_menu_bar){
        wattron(menu_bar_window,COLOR_PAIR(2));
    }
    mvwprintw(menu_bar_window,0,17,"Attribute");
    wattroff(menu_bar_window,COLOR_PAIR(2));
    if (menu_bar_selection == 3 && accessing_menu_bar){
        wattron(menu_bar_window,COLOR_PAIR(2));
    }
    mvwprintw(menu_bar_window,0,30,"Object");
    wattroff(menu_bar_window,COLOR_PAIR(2));
    wrefresh(menu_bar_window);
    if (menu_bar_option_selection >= 0){
        wbkgd(menu_bar_options_window[menu_bar_selection], COLOR_PAIR(1));
        wborder(menu_bar_options_window[menu_bar_selection],0,0,' ',0,ACS_VLINE,ACS_VLINE,0,0);
        for (int i = 0; i < menu_bar_options_size; i++){
            if (i == menu_bar_option_selection){
                wattron(menu_bar_options_window[menu_bar_selection],COLOR_PAIR(2));
            }
            mvwprintw(menu_bar_options_window[menu_bar_selection],i,1,menu_bar_options[i]);
            wattroff(menu_bar_options_window[menu_bar_selection],COLOR_PAIR(2));
        }
        wrefresh(menu_bar_options_window[menu_bar_selection]);
    }
}

void printToFile(char * filename){
    vector<Line *> line;

    line.push_back(new Line(new Point(100,100),new Point(200,200)));
    line.push_back(new Line(new Point(1,1),new Point(2,2)));

    ofstream file;
    file.open("lines.txt");
    
    for (vector<Line *>::iterator it = line.begin(); it != line.end(); it++){
        Point *P1 = (*it)->getP1();
        Point *P2 = (*it)->getP2();

        file << P1->getX() << ' ' << P1->getY() << '|' << P2->getX() << ' ' << P2->getY() << endl;
    }

    file.close();
}

void file_gui(char selection, int max_x_screen, int max_y_screen){
    if (selection < 0){
        return;
    }

    WINDOW * window = newwin(10,40,max_y_screen/2-5,max_x_screen/2-20);
    char dummy[100];
    char test[100];
    memset(test,'\0',100);

    box(window,0,0);
    wbkgd(window,COLOR_PAIR(1));

    wrefresh(window);
    
    mvscanw(30,30,dummy);

    echo();
    switch(selection){
        case(0):
            break;
        case(1):
            mvwprintw(window,3,11,"Enter file to open");
            wattron(window,A_REVERSE);
            mvwprintw(window,5,2,"                                    ");
            wrefresh(window);
            mvwscanw(window,5,2,test);
            wattroff(window,A_REVERSE);
            break;
        case(2):
            mvwprintw(window,3,13,"Enter filename");
            wattron(window,A_REVERSE);
            mvwprintw(window,5,2,"                                    ");
            wrefresh(window);
            mvwscanw(window,5,2,test);
            printToFile(test);
            wattroff(window,A_REVERSE);
            break;
        case(3):
            out = true;
            break;
    }

    wbkgd(window,COLOR_BLACK);
    wclear(window);
    wrefresh(window);
    noecho();
}

string color = "white";
int dash = 0;
int thickness = 1;
bool quit =  false;

void userInput(int fd){
    ssize_t n;
    struct input_event ev;

    while(!quit){
        n = read(fd, &ev, sizeof ev);
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else if (n != sizeof ev) {
            errno = EIO;
            break;
        }
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
            if (ev.value == 1){
                if ((ev.code  == 105) && (dash >= 1)){ // left key
                    dash--;
                } else if ((ev.code == 106) && (dash < 5)){ // right key
                    dash++;
                } else if ((ev.code == 103) && (thickness < 3)){ // up key
                    thickness++;
                } else if ((ev.code == 108) && (thickness > 1)){ // down key
                    thickness--;
                } else if (ev.code == KEY_G){
                    color = "green";
                } else if (ev.code == KEY_B){
                    color = "blue";
                } else if (ev.code == KEY_R){
                    color = "red";
                } else if (ev.code == KEY_T){
                    color = "turquoise";
                } else if (ev.code == KEY_P){
                    color = "purple";
                } else if (ev.code == KEY_W){
                    color = "white";
                } else if (ev.code == KEY_Y){
                    color = "yellow";
                } else if (ev.code == KEY_O){
                    color = "orange";
                } else if (ev.code == KEY_M){
                    color = "magenta";
                } else if (ev.code == KEY_Q){
					quit = true;
				}
				//cout << "Dash in input : " << dash << "\n";
				cout << "Thickness in input : " << thickness << "\n";
            }
        }
    }
}

int main(int argc, char** argv){
    int fbfd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize;
    char *fbp;
	char c;
	string prev_color;
	int prev_dash;
	int prev_thickness;
	mutex mtx;
	bool hasRendered=true;

    vector<Line *> line;
    vector<Polygon *> polygon;

    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        // Framebuffer can't be opened
        exit(1);
    }

    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        // Error reading fixed screen information
        exit(2);
    }

    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        // Error reading variable screen information
        exit(3);
    }

    // Calculating the screen size in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the framebuffer into memory
    fbp = (char *) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        // Mapping failed
        exit(4);
    }

    const char *dev = "/dev/input/event2";
    int fd = open(dev, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }
	struct timespec delay;      // delay variable
    delay.tv_sec = 0;
    delay.tv_nsec = 10000000;

	thread inputter (userInput,fd);
	clear_screen(1024,768,fbp,vinfo,finfo);
	
	struct RGB rgb;
	while(!quit){
		//cout << "Thickness in output : " << dash << "\n";
		//cout << "Previous Thickness in output : " << prev_dash << "\n";
		if(color=="white"){
			rgb.r = 255;
			rgb.g = 255;
			rgb.b = 255;
		}
		else if(color=="green"){
			rgb.r = 0;
			rgb.g = 255;
			rgb.b = 0;
		}
		else if(color=="blue"){
			rgb.r = 0;
			rgb.g = 0;
			rgb.b = 255;
		}
		else if(color=="red"){
			rgb.r = 255;
			rgb.g = 0;
			rgb.b = 0;
		}
		else if(color=="yellow"){
			rgb.r = 255;
			rgb.g = 255;
			rgb.b = 0;
		}
		else if(color=="magenta"){
			rgb.r = 255;
			rgb.g = 0;
			rgb.b = 255;
		}
		else if(color=="purple"){
			rgb.r = 128;
			rgb.g = 0;
			rgb.b = 128;
		}
		else if(color=="turqoise"){
			rgb.r = 64;
			rgb.g = 224;
			rgb.b = 208;
		}
		else if(color=="orange"){
			rgb.r = 255;
			rgb.g = 99;
			rgb.b = 71;
		}
		Point *P1 = new Point(100,100);
		Point *P2 = new Point(200,200);
		Line* line = new Line(P1, P2);
		/*if(((color!=prev_color) or (dash != prev_dash) or (thickness != prev_thickness)) and (hasRendered)){
			color = prev_color;
			dash = prev_dash;
			thickness = prev_thickness;
		}*/
		line->setRGB(rgb);
		line->setDash(dash);
		line->setThickness(thickness);
		line->render(fbp, vinfo, finfo);
		//hasRendered=true;
		mtx.lock();
		prev_color = color;
		prev_dash = dash;
		prev_thickness = thickness;
		mtx.unlock();
		if((color!=prev_color) or (dash != prev_dash) or (thickness != prev_thickness)){
			clear_screen(1024,768,fbp,vinfo,finfo);
			//hasRendered=false;
		}
		delete(line);
	}
	// Polygon polygon;

	// polygon.addPoint(new Point(100,100));
	// polygon.addPoint(new Point(200,200));
	// polygon.addPoint(new Point(300,300));

	// polygon.render(fbp,vinfo,finfo);
	munmap(fbp, screensize);
	close(fbfd);
	inputter.join();
    return 0;
}
