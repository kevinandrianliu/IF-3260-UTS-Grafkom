#include <cerrno>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <iostream>
#include <unistd.h>
#include <ncurses.h>

#include "util/func_util.h"
#include "objects.h"
#include "objects_util.h"

using namespace std;

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

int main(int argc, char** argv){
    int fbfd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize;
    char *fbp;

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

    struct RGB rgb;
    rgb.r = 255;
    rgb.g = 0;
    rgb.b = 0;

    /*** BEGIN TESTING ***/
    addLine(&line, new Line(new Point(5,7), new Point(100,200)));
    addLine(&line, new Line(new Point(40,18), new Point(400,200)));
    addLine(&line, new Line(new Point(63,127), new Point(30,700)));

    cout << "Vector line" << endl;
    for (Line *e : line) {
        cout << "Line" << endl;
        e->render(fbp, vinfo, finfo);
    }

    Line *f = selectLine(&line, 0);
    f->render(fbp, vinfo, finfo);

    deleteLine(&line, 2);
    cout << "New vector line" << endl;
    for (Line *e : line) {
        e->render(fbp, vinfo, finfo);
    }

    cout << "Input polygon 0" << endl;
    addPolygon(&polygon);
    cout << "Input polygon 1" << endl;
    addPolygon(&polygon);
    for (Polygon *e : polygon) {
        e->render(fbp, vinfo, finfo);
    }

    deletePolygon(&polygon, 0);

    cout << "New vector polygon" << endl;
    for (Polygon *e : polygon) {
        e->render(fbp, vinfo, finfo);
    }

    int xmin = getXMin(&line, &polygon);
    cout << xmin << endl;

    /*** END TESTING ***/

    munmap(fbp, screensize);

    close(fbfd);
    return 0;
}