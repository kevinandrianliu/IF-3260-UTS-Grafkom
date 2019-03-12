#ifndef __CLASSUTIL_HPP__
#define __CLASSUTIL_HPP__

#include <linux/fb.h>
using namespace std;

class Object {
    public:
        Object();
        virtual ~Object();

        virtual void render(char* fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo) = 0;
};

#endif