#include "objects_util.h"
#include <iostream>
#include <fstream>
#include <ncurses.h>

using namespace std;


void addLine(vector<Line *> *line, Line *l) {
    line->push_back(l);
}

void addPolygon(vector<Polygon *> *polygon, Polygon *p) {
    polygon->push_back(p);
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
        if (x > e->getP1()->getX()) {
            x = e->getP1()->getX();
        } else if (x > e->getP2()->getX()) {
            x = e->getP2()->getX();
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
        if (x > e->getP1()->getY()) {
            x = e->getP1()->getY();
        } else if (x > e->getP2()->getY()) {
            x = e->getP2()->getY();
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
        if (x < e->getP1()->getX()) {
            x = e->getP1()->getX();
        } else if (x < e->getP2()->getX()) {
            x = e->getP2()->getX();
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
        if (x < e->getP1()->getY()) {
            x = e->getP1()->getY();
        } else if (x < e->getP2()->getY()) {
            x = e->getP2()->getY();
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
    bresenham(0, SCRN_HEIGHT, SCRN_WIDTH, SCRN_HEIGHT, rgb, framebuffer, vinfo, finfo);
    bresenham(0, SCRN_HEIGHT-20, SCRN_WIDTH, SCRN_HEIGHT-20, rgb, framebuffer, vinfo, finfo);
    bresenham(0, SCRN_HEIGHT-20, 0, SCRN_HEIGHT, rgb, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH, SCRN_HEIGHT-20, SCRN_WIDTH, SCRN_HEIGHT, rgb, framebuffer, vinfo, finfo);

    //Render inner scrollbar
    int viewWidth = getXMax(line, polygon) - getXMin(line, polygon);
    int barWidth = SCRN_WIDTH / viewWidth * SCRN_WIDTH;

    int offsetBar = (0 - getXMin(line, polygon)) / viewWidth * SCRN_WIDTH;

    bresenham(offsetBar, SCRN_HEIGHT-20, offsetBar, SCRN_HEIGHT, rgb, framebuffer, vinfo, finfo);
    bresenham(offsetBar + barWidth, SCRN_HEIGHT-20, offsetBar + barWidth, SCRN_HEIGHT, rgb, framebuffer, vinfo, finfo);
}

void renderVerticalBar(vector<Line *> *line, vector<Polygon *> *polygon, struct RGB rgb, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo) {
    //Render scrollbar box
    bresenham(SCRN_WIDTH, 0, SCRN_WIDTH, SCRN_HEIGHT, rgb, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH-20, 0, SCRN_WIDTH-20, SCRN_HEIGHT, rgb, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH, SCRN_HEIGHT, SCRN_WIDTH-20, SCRN_HEIGHT, rgb, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH-20, 0, SCRN_WIDTH, 0, rgb, framebuffer, vinfo, finfo);

    //Render inner scrollbar
    int viewWidth = getYMax(line, polygon) - getYMin(line, polygon);
    int barWidth = SCRN_HEIGHT / viewWidth * SCRN_HEIGHT;

    int offsetBar = (0 - getYMin(line, polygon)) / viewWidth * SCRN_HEIGHT;

    bresenham(SCRN_WIDTH-20, offsetBar, SCRN_WIDTH, offsetBar, rgb, framebuffer, vinfo, finfo);
    bresenham(SCRN_WIDTH-20, offsetBar+barWidth, SCRN_WIDTH, offsetBar+barWidth, rgb, framebuffer, vinfo, finfo);
}

Line* parseToLine(char * P1, char * P2){
    int P1_x, P1_y, P2_x, P2_y;
    string P1_string(P1);
    string P2_string(P2);
    string delimiter = ",";
    struct RGB rgb;
    rgb.r = rgb.g = rgb.b = 255;

    int start = 0;
    int end = P1_string.find(delimiter);
    P1_x = stoi(P1_string.substr(start, end - start));
    start = end + delimiter.length();
    end = P1_string.find(delimiter, start);
    P1_y = stoi(P1_string.substr(start, end));

    start = 0;
    end = P2_string.find(delimiter);
    P2_x = stoi(P2_string.substr(start, end - start));
    start = end + delimiter.length();
    end = P2_string.find(delimiter, start);
    P2_y = stoi(P2_string.substr(start, end));

    Line * line = new Line(new Point(P1_x,P1_y), new Point(P2_x,P2_y));
    line->setRGB(rgb);

    return line;
}

bool parseToPoint(Point * point, char *P){
    string stop_condition("-999,-999");
    string P_string(P);

    if (stop_condition.compare(P_string) == 0){
        return false;
    } else {
        int P_x, P_y;
        string delimiter(",");

        int start = 0;
        int end = P_string.find(delimiter);
        P_x = stoi(P_string.substr(start, end - start));
        start = end + delimiter.length();
        end = P_string.find(delimiter, start);
        P_y = stoi(P_string.substr(start, end));

        point->setX(P_x);
        point->setY(P_y);

        return true;
    }
}