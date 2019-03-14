#ifndef __OBJECTS_UTIL_HPP__
#define __OBJECTS_UTIL_HPP__
#include <vector>
#include "objects.h"
using namespace std;

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

#endif