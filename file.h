#ifndef __FILE_HPP__
#define __FILE_HPP__
#include "objects.h"
#include <string>
using namespace std;


void save_lines(vector<Line*> lines, char * filename);
void save_polygons(vector<Polygon*> polygons, char * filename);
vector<Line*> load_lines(char* filename);
vector<Polygon*> load_polygons(char* filename);
vector<string> split(string str, string tok);

#endif