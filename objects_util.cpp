#include "objects_util.h"
#include <iostream>
using namespace std;


void addLine(vector<Line *> *line, Line *l) {
    line->push_back(l);
}

void addPolygon(vector<Polygon *> *polygon) {
    int a, b;
    polygon->push_back(new Polygon);
    Polygon *p = polygon->back();
    cout << "Input points, end with negative number:" << endl;
    do {
        cin >> a;
        cin >> b;
        if ((a > 0) && (b > 0)) {
            p->addPoint(new Point(a,b));
        }
    } while ((a > 0) && (b > 0));
}

Line* selectLine(vector<Line *> *line, int i) {
    //Index start from 0
    return line->at(i);
}

void deleteLine(vector<Line *> *line, int i) {
    //Index start from 0
    line->erase(line->begin() + i);
}

Polygon* selectPolygon(vector<Polygon *> *polygon, int i) {
    //Index start from 0
    return polygon->at(i);
}

void deletePolygon(vector<Polygon *> *polygon, int i) {
    //Index start from 0
    polygon->erase(polygon->begin() + i);
}

int getXMin(vector<Line *> *line, vector<Polygon *> *polygon) {
    int x = 1024;
    vector<Line *>::iterator itl;
    vector<Polygon *>::iterator itp;
    for (itl = line->begin(); itl != line->end(); itl++) {
        Line *e = *itl;
        if (x > e->getP1().getX()) {
            x = e->getP1().getX();
        } else if (x > e->getP2().getX()) {
            x = e->getP2().getX();
        }
    }
    for (itp = polygon->begin(); itp != polygon->end(); itp++) {
        Polygon *t = *itp;
        for (Point *e : t->getPointVector()) {
            if (x > e->getX()) {
                x = e->getX();
            } else if (x > e->getX()) {
                x = e->getX();
            }
        }
    }
    return x;
}

int getYMin(vector<Line *> *line, vector<Polygon *> *polygon) {
    int x = 768;
    vector<Line *>::iterator itl;
    vector<Polygon *>::iterator itp;
    for (itl = line->begin(); itl != line->end(); itl++) {
        Line *e = *itl;
        if (x > e->getP1().getY()) {
            x = e->getP1().getY();
        } else if (x > e->getP2().getY()) {
            x = e->getP2().getY();
        }
    }
    for (itp = polygon->begin(); itp != polygon->end(); itp++) {
        Polygon *t = *itp;
        for (Point *e : t->getPointVector()) {
            if (x > e->getY()) {
                x = e->getY();
            } else if (x > e->getY()) {
                x = e->getY();
            }
        }
    }
    return x;
}

int getXMax(vector<Line *> *line, vector<Polygon *> *polygon) {
    int x = 0;
    vector<Line *>::iterator itl;
    vector<Polygon *>::iterator itp;
    for (itl = line->begin(); itl != line->end(); itl++) {
        Line *e = *itl;
        if (x < e->getP1().getX()) {
            x = e->getP1().getX();
        } else if (x < e->getP2().getX()) {
            x = e->getP2().getX();
        }
    }
    for (itp = polygon->begin(); itp != polygon->end(); itp++) {
        Polygon *t = *itp;
        for (Point *e : t->getPointVector()) {
            if (x < e->getX()) {
                x = e->getX();
            } else if (x < e->getX()) {
                x = e->getX();
            }
        }
    }
    return x;
}


int getYMax(vector<Line *> *line, vector<Polygon *> *polygon) {
    int x = 0;
    vector<Line *>::iterator itl;
    vector<Polygon *>::iterator itp;
    for (itl = line->begin(); itl != line->end(); itl++) {
        Line *e = *itl;
        if (x < e->getP1().getY()) {
            x = e->getP1().getY();
        } else if (x < e->getP2().getY()) {
            x = e->getP2().getY();
        }
    }
    for (itp = polygon->begin(); itp != polygon->end(); itp++) {
        Polygon *t = *itp;
        for (Point *e : t->getPointVector()) {
            if (x < e->getY()) {
                x = e->getY();
            } else if (x < e->getY()) {
                x = e->getY();
            }
        }
    }
    return x;
}

void renderHorizontalBar(vector<Line *> *line, vector<Polygon *> *polygon, struct RGB rgb, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo) {


    //Render scrollbar box
    bresenham(0, SCRN_HEIGHT, SCRN_WIDTH, SCRN_HEIGHT, rgb, 0, framebuffer, vinfo, finfo);
    bresenham(0, SCRN_HEIGHT-20, SCRN_WIDTH, SCRN_HEIGHT-20, rgb, 0, framebuffer, vinfo, finfo);
    bresenham(0, SCRN_HEIGHT-20, 0, SCRN_HEIGHT, rgb, 0, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH, SCRN_HEIGHT-20, SCRN_WIDTH, SCRN_HEIGHT, rgb, 0, framebuffer, vinfo, finfo);

    //Render inner scrollbar
    int viewWidth = getXMax(line, polygon) - getXMin(line, polygon);
    int barWidth = SCRN_WIDTH / viewWidth * SCRN_WIDTH;

    int offsetBar = (0 - getXMin(line, polygon)) / viewWidth * SCRN_WIDTH;

    bresenham(offsetBar, SCRN_HEIGHT-20, offsetBar, SCRN_HEIGHT, rgb, 0, framebuffer, vinfo, finfo);
    bresenham(offsetBar + barWidth, SCRN_HEIGHT-20, offsetBar + barWidth, SCRN_HEIGHT, rgb, 0, framebuffer, vinfo, finfo);
}

void renderVerticalBar(vector<Line *> *line, vector<Polygon *> *polygon, struct RGB rgb, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo) {
    //Render scrollbar box
    bresenham(SCRN_WIDTH, 0, SCRN_WIDTH, SCRN_HEIGHT, rgb, 0, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH-20, 0, SCRN_WIDTH-20, SCRN_HEIGHT, rgb, 0, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH, SCRN_HEIGHT, SCRN_WIDTH-20, SCRN_HEIGHT, rgb, 0, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH-20, 0, SCRN_WIDTH, 0, rgb, 0, framebuffer, vinfo, finfo);

    //Render inner scrollbar
    int viewWidth = getYMax(line, polygon) - getYMin(line, polygon);
    int barWidth = SCRN_HEIGHT / viewWidth * SCRN_HEIGHT;

    int offsetBar = (0 - getYMin(line, polygon)) / viewWidth * SCRN_HEIGHT;

    bresenham(SCRN_WIDTH-20, offsetBar, SCRN_WIDTH, offsetBar, rgb, 0, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH-20, offsetBar+barWidth, SCRN_WIDTH, offsetBar+barWidth, rgb, 0, framebuffer, vinfo, finfo);
}