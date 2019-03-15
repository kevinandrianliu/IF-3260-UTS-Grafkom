#ifndef __OBJECTS_UTIL_HPP__
#define __OBJECTS_UTIL_HPP__
#include <vector>
#include "objects.h"
#include "util/func_util.h"
using namespace std;

#define SCRN_WIDTH 1024
#define SCRN_HEIGHT 768

/** VECTOR PROCESSING FUNCTION **/
void addLine(vector<Line *> *line, Line *l);
void addPolygon(vector<Polygon *> *polygon);
Line* selectLine(vector<Line *> *line, int i);
void deleteLine(vector<Line *> *line, int i);
Polygon* selectPolygon(vector<Polygon *> *polygon, int i);
void deletePolygon(vector<Polygon *> *polygon, int i);
int getXMin(vector<Line *> *line, vector<Polygon *> *polygon);
int getYMin(vector<Line *> *line, vector<Polygon *> *polygon);
int getXMax(vector<Line *> *line, vector<Polygon *> *polygon);
int getXMax(vector<Line *> *line, vector<Polygon *> *polygon);

/** SCROLLBAR RENDER FUNCTION **/
void renderHorizontalBar(vector<Line *> *line, vector<Polygon *> *polygon, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo);
void renderVerticalBar(vector<Line *> *line, vector<Polygon *> *polygon, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo);

/** STRING PARSING **/
Line* parseToLine(char * P1, char * P2);
bool parseToPoint(Point * point, char *P);

#endif