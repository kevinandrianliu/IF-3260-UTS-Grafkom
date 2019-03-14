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

char menu_bar_option_selection = 0;
char menu_bar_selection = 0;

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
                
            }
        }
    }
}

void drawMenuBar(WINDOW** menu_bar_window){
    char ** menu_bar_options;

    switch(menu_bar_selection){
        case(0):
            menu_bar_options = (char**) malloc (5 * sizeof (char *));
            menu_bar_options[0] = "File";
            menu_bar_options[1] = "New";
            menu_bar_options[2] = "Open";
            menu_bar_options[3] = "Save";
            menu_bar_options[4] = "Exit";
            break;
        case(1):
            menu_bar_options = (char**) malloc (5 * sizeof (char *));
            menu_bar_options[0] = "File";
            menu_bar_options[1] = "New";
            menu_bar_options[2] = "Open";
            menu_bar_options[3] = "Save";
            menu_bar_options[4] = "Exit";
            break;
        case(2):

        case(3):

        default:
            break;
    }

    box(menu_bar_window[0],0,0);
    mvwprintw(menu_bar_window[0],0,0,menu_bar_options[0]);
    mvwprintw(menu_bar_window[0],1,0,menu_bar_options[1]);
    mvwprintw(menu_bar_window[0],2,0,menu_bar_options[2]);
    mvwprintw(menu_bar_window[0],3,0,menu_bar_options[3]);
    mvwprintw(menu_bar_window[0],4,0,menu_bar_options[4]);
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

    const char * dev = "/dev/input/event2";
    int fd = open(dev,O_RDONLY);
    if (fd == -1){
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }

    // thread inputter (userInput,fd);

    struct RGB menu_bar_background;
    menu_bar_background.r = 204;
    menu_bar_background.g = 204;
    menu_bar_background.b = 204;

    initscr();

    WINDOW ** menu_bar_window = (WINDOW**) malloc (4*sizeof(WINDOW*));
    menu_bar_window[0] = newwin(6,15,0,0);
    drawMenuBar(menu_bar_window);
    
    // move(0,0);
    // printw("File");
    // move(0,8);
    // printw("View");
    // move(0,16);
    // printw("Attribute");
    // move(0,29);
    // printw("Object");
    
    refresh();
    wrefresh(menu_bar_window[0]);

    delwin(menu_bar_window[0]);
    free(menu_bar_window);
    endwin();

    // Line line(new Point(100,100), new Point(100,100));

    // line.render(fbp,vinfo,finfo);

    // Polygon polygon;

    // polygon.addPoint(new Point(100,100));
    // polygon.addPoint(new Point(200,200));
    // polygon.addPoint(new Point(300,300));

    // polygon.render(fbp,vinfo,finfo);

    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}