<<<<<<< HEAD
=======

>>>>>>> 15b658d8233eeac1edcd8263c581280501901d10
#ifndef __OBJECTS_HPP__
#define __OBJECTS_HPP__

#include <vector>
#include "util/class_util.h"
#include "util/func_util.h"
using namespace std;

class Point {
    public:
        Point(int x, int y);
        ~Point();

        int getX();
        int getY();
        void setX(int x);
        void setY(int y);

    private:
        int x;
        int y;
};

class Line : public Object {
    public:
        Line(Point * P1, Point * P2);
        ~Line();
<<<<<<< HEAD
        
        Point* getP1();
        Point* getP2();
        struct RGB getRGB();
        int getDash();
        int getThickness();
        void setP1(Point* P1);
        void setP2(Point* P2);
        void setRGB(struct RGB rgb);
        void setDash(int dash);
        void setThickness(int thickness);
=======

        Point getP1();
        Point getP2();
	struct RGB getRGB();
	int getDash();
	int getThickness();
        void setP1(Point* P1);
        void setP2(Point* P2);
	void setRGB(RGB rgb);
	void setDash(int dash);
	void setThickness(int thickness);
>>>>>>> 15b658d8233eeac1edcd8263c581280501901d10
        
        void render(char* fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo);
        
        void zoomIn(int k);
        void zoomOut(int k);
        void pan(int direction);
    private:
        Point * P1;
        Point * P2;
        struct RGB rgb;
<<<<<<< HEAD
        int dash;
    	int thickness;
=======
	int dash;
	int thickness;
>>>>>>> 15b658d8233eeac1edcd8263c581280501901d10
};

class Polygon : public Object {
    public:
<<<<<<< HEAD
        Polygon(struct RGB rgb);
=======
        Polygon();
>>>>>>> 15b658d8233eeac1edcd8263c581280501901d10
        ~Polygon();

        vector<Point *> getPointVector();
        
<<<<<<< HEAD
        struct RGB getRGB();
        void setRGB(struct RGB rgb);

=======
>>>>>>> 15b658d8233eeac1edcd8263c581280501901d10
        void addPoint(Point * P);
        void render(char* fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo);

        void zoomIn(int k);
        void zoomOut(int k);
        void pan(int direction);
    private:
<<<<<<< HEAD
        struct RGB rgb;
        vector<Point *> point_vector;
};
#endif
=======
        vector<Point *> point_vector;
};
#endif
>>>>>>> 15b658d8233eeac1edcd8263c581280501901d10
