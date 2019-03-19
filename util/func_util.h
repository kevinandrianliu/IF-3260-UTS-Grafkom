#ifndef __FUNC_UTIL_HPP__
#define __FUNC_UTIL_HPP__

#include <linux/fb.h>

using namespace std;

struct RGB {
    char r;
    char g;
    char b;
};

void clear_screen(unsigned int x_size, unsigned int y_size, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo);

void bresenham(int x0, int y0, int x1, int y1, struct RGB rgb, int dash, int thickness, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo);

void pixelColor(struct RGB rgb, char *fbp, long int location);

char checkPixelAround(int x, int y, char * fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo);

void rasterScan(int x_min, int y_min, int x_max, int y_max, struct RGB rgb, char * fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo);


#endif
