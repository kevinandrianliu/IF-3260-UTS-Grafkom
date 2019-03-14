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
#include <thread>
#include <cstring>
#include <ctime>
#include <mutex>
#include "util/func_util.h"
#include "objects.h"

using namespace std;

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

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
