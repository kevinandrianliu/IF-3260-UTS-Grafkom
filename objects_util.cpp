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

void renderFillPolygon(Polygon* polygon, struct RGB rgb, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    int size = polygon->getPointVector().size();
    int x[size];
    int y[size];

    int i = 0;
    for (Point *e : polygon->getPointVector()) {
        x[i] = e->getX();
        i++;
    }

    i = 0;
    for (Point *e : polygon->getPointVector()) {
        y[i] = e->getY();
        i++;
    }

    //init reference tabel
    float edgeTabel[size][4];
    for (i = 0; i< size; i++){
        if (x[i] != x[i+1]){
            edgeTabel[i][1] = std::min(y[i], y[i+1]);
            edgeTabel[i][2] = std::max(y[i], y[i+1]);
            edgeTabel[i][3] = std::min(x[i], x[i+1]);
            edgeTabel[i][4] = (x[i+1]-x[i])/(y[i+1]-y[i]);
        }
    }

    vector< pair <int,int> > global_list;
    for (i = 0; i< size; i++){
        global_list.push_back(make_pair((int)edgeTabel[i][1],i)); //ymin & indeks tabel
    }
    sort(global_list.begin(), global_list.end());

    //init y_scan value
    int y_scan = std::min_element(y, y + size);

    vector< pair <int,int> > active_list;

    //while global or active list not empty
    while ((global_list.size() > 0) || (active_list.size() > 0)) {

        for (vector<pair <int,int>>::iterator it = global_list.begin(); it != global_list.end(); it++){
            if (y_scan == it->first){ //y_scan = ymin di ref tabel
                //input ke active list
                i = it->second;
                active_list.push_back(make_pair((int)edgeTabel[i][3],i)); //ymax & indeks tabel
                //erase from global list
                global_list.erase(it);
            }        
        }

        //sort active list
        sort(active_list.begin(), active_list.end());

        for (int j = 0; j < active_list.size(); j+=2){
            for (int x_scan = active_list[j].first; x_scan < active_list[j+1].first; x_scan++){
                long int mem_location = (x_scan + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y_scan + vinfo.yoffset) * finfo.line_length;

                pixelColor(rgb,framebuffer,mem_location);
            }
        }

        y_scan++;

        //update xval
        int k;
        for (vector<pair <int,int>>::iterator it = active_list.begin(); it != active_list.end(); it++){
            k = it->second;
            if(edgeTabel[k][2]+1 == y_scan){
                //remove if ymax=y_scan
                active_list.erase(it);
            } else {
                edgeTabel[k][3] =+ edgeTabel[k][4];
                it->first = (int)edgeTabel[k][3]; 
            }  
        };
        sort(active_list.begin(),active_list.end());

    }  

}