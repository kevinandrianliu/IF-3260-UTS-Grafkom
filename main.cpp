#include <cerrno>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include <cstring>
#include <thread>

#include "util/func_util.h"
#include "objects.h"

using namespace std;

char menu_bar_option_selection = -1;
char menu_bar_selection = 0;
int key_code = 0x00;
bool refresh_screen = false;
bool accessing_menu_bar = false;

void userInput(int fd){
    ssize_t n;
    struct input_event ev;

    bool out = false;

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

int main(int argc, char** argv){
    int fbfd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize;
    char *fbp;

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

    const char * dev = "/dev/input/event4";
    int fd = open(dev,O_RDONLY);
    if (fd == -1){
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }

    thread inputter (userInput,fd);

    struct RGB menu_bar_background;
    menu_bar_background.r = 204;
    menu_bar_background.g = 204;
    menu_bar_background.b = 204;

    initscr();
    start_color();
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_RED);

    int max_x_screen, max_y_screen;
    getmaxyx(stdscr,max_y_screen,max_x_screen);

    WINDOW ** menu_bar_options_window = (WINDOW**) malloc (4*sizeof(WINDOW*));
    menu_bar_options_window[0] = newwin(5,18,1,0);
    menu_bar_options_window[1] = newwin(7,18,1,8);
    menu_bar_options_window[2] = newwin(4,18,1,16);
    menu_bar_options_window[3] = newwin(5,18,1,29);
    WINDOW * menu_bar_window = newwin(1,max_x_screen,0,0);

    clear();
    while(1){
        if (refresh_screen){
            clear();
            drawMenuBar(menu_bar_options_window,menu_bar_window);
            refresh_screen = false;
        }

        if (key_code == KEY_ESC){
            break;
        }
    }

    delwin(menu_bar_options_window[0]);
    delwin(menu_bar_options_window[1]);
    delwin(menu_bar_options_window[2]);
    delwin(menu_bar_options_window[3]);
    
    free(menu_bar_options_window);
    endwin();

    munmap(fbp, screensize);
    close(fbfd);

    inputter.join();

    return 0;
}