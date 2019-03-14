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

using namespace std;

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

vector<Line *> line;
vector<Polygon *> polygon;

void addLine(Line *l);
void addPolygon();
Line* selectLine(int i);
void deleteLine(int i);
Polygon* selectPolygon(int i);
void deletePolygon(int i);

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

    struct RGB rgb;
    rgb.r = 255;
    rgb.g = 0;
    rgb.b = 0;

    // Line line(new Point(100,100), new Point(100,100));

    // line.render(fbp,vinfo,finfo);

    // Polygon polygon;

    // polygon.addPoint(new Point(100,100));
    // polygon.addPoint(new Point(200,200));
    // polygon.addPoint(new Point(300,300));

    // polygon.render(fbp,vinfo,finfo);

    /*** BEGIN TESTING ***/
    addLine(new Line(new Point(5,7), new Point(100,200)));
    addLine(new Line(new Point(40,18), new Point(400,200)));
    addLine(new Line(new Point(63,127), new Point(30,700)));

    cout << "Vector line" << endl;
    for (Line *e : line) {
        e->render(fbp, vinfo, finfo);
    }

    Line *f = selectLine(0);
    f->render(fbp, vinfo, finfo);

    deleteLine(2);
    cout << "New vector line" << endl;
    for (Line *e : line) {
        e->render(fbp, vinfo, finfo);
    }

    cout << "Input polygon 0" << endl;
    addPolygon();
    cout << "Input polygon 1" << endl;
    addPolygon();
    for (Polygon *e : polygon) {
        e->render(fbp, vinfo, finfo);
    }

    deletePolygon(0);
    
    cout << "New vector polygon" << endl;
    for (Polygon *e : polygon) {
        e->render(fbp, vinfo, finfo);
    }

    /*** END TESTING ***/

    munmap(fbp, screensize);

    close(fbfd);
    return 0;
}

void addLine(Line *l) {
    line.push_back(l);
}

void addPolygon() {
    int a, b;
    polygon.push_back(new Polygon);
    Polygon *p = polygon.back();
    cout << "Input points, end with negative number:" << endl;
    do {
        cin >> a;
        cin >> b;
        if ((a > 0) && (b > 0)) {
            p->addPoint(new Point(a,b));
        }
    } while ((a > 0) && (b > 0));
}

Line* selectLine(int i) {
    //Index start from 0
    return line[i];
}

void deleteLine(int i) {
    //Index start from 0
    line.erase(line.begin() + i);
}

Polygon* selectPolygon(int i) {
    //Index start from 0
    return polygon[i];
}

void deletePolygon(int i) {
    //Index start from 0
    polygon.erase(polygon.begin() + i);
}