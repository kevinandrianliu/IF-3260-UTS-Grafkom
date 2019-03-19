#include <unistd.h>
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include "objects.h"
using namespace std;

void save_lines(vector<Line*> lines);

void save_polygons(vector<Polygon*> polygons);

vector<Line*> load_lines(char* filename);

vector<Polygon*> load_polygons(char* filename);

vector<string> split(string str, string tok);


int main(int argc, char** argv){

    vector<Line* > lines, lines2;
    vector<Polygon* > polygons;

    Line* line = new Line(new Point(100,100),new Point(200,200));
    line->setRGB({100,100,100});
    line->setDash(0);
    line->setThickness(5);
    lines.push_back(line);

    Line* line2 = new Line(new Point(50,100),new Point(50,200));
    line2->setRGB({50,50,50});
    line2->setDash(3);
    line2->setThickness(5);
    lines.push_back(line2);
    //lines.push_back(new Line(new Point(1,1),new Point(2,2)));

    Polygon* polygon = new Polygon;
    polygon->addPoint(new Point(100,100));
    polygon->addPoint(new Point(200,200));
    polygon->addPoint(new Point(300,300));
    polygons.push_back(polygon);

    Polygon* polygon2 = new Polygon;
    polygon2->addPoint(new Point(110,110));
    polygon2->addPoint(new Point(220,220));
    polygon2->addPoint(new Point(330,330));
    polygons.push_back(polygon2);

    // polygon.addPoint(new Point(100,100));
    // polygon.addPoint(new Point(200,200));
    // polygon.addPoint(new Point(300,300));

    // polygon.render(fbp,vinfo,finfo);

    save_lines(lines);
    save_polygons(polygons);

    lines2 = load_lines("lines.txt");
    for (vector<Line *>::iterator it = lines.begin(); it != lines.end(); it++){
	cout << (*it)->getP1().getX() << "," << (*it)->getP2().getY() << endl;
    }

    return 0;
}


void save_lines(vector<Line* > lines) {

    ofstream fout("lines.txt", ios_base::out | ios_base::binary);
    
    for (vector<Line *>::iterator it = lines.begin(); it != lines.end(); it++){
	RGB rgb = (*it)->getRGB();
	int dash = (*it)->getDash();
	int thickness = (*it)->getThickness();

        fout << (*it)->getP1().getX() << ',' << (*it)->getP1().getY() << '|' << (*it)->getP2().getX() << ',' << (*it)->getP2().getY() << '|' << rgb.r << ',' << rgb.g << ',' << rgb.b << '|' << dash << '|' << thickness << endl;
    }

    fout.close();
}

void save_polygons(vector<Polygon* > polygons) {

    ofstream fout("polygons.txt");
    for (vector<Polygon *>::iterator it = polygons.begin(); it != polygons.end(); it++) {

        vector <Point*> pts = (*it)->getPointVector();
        for (vector<Point *>::iterator it2 = pts.begin(); it2 != pts.end(); it2++) {
            fout << (*it2)->getX() << ',' << (*it2)->getY();
	    if(it2 != pts.end()-1) { fout << '|';}
        }
	fout << endl;
    }
    fout.close();
}

vector<Line*> load_lines(char* filename) {
	vector<Line*> lines;
	ifstream fin(filename);
	string data;
	while(getline(fin,data)){
		char* info;
		vector<string> datas;
		char* writable = new char[data.length()+1];
		strcpy(writable, data.c_str());
		writable[data.length()] = '\0';
		info = strtok(writable," ,|\n");

		while(info!=NULL) {
			datas.push_back(string(info));
			info = strtok(NULL," ,|\n");
		}
		delete [] writable;
		
		int point1x = stoi(datas[0]);
		int point1y = stoi(datas[1]);
		int point2x = stoi(datas[2]);
		int point2y = stoi(datas[3]);
		Line* line = new Line(new Point(point1x,point1y),new Point(point2x,point2y));

		char* r = new char[datas[4].length()+1];
		char* g = new char[datas[5].length()+1];
		char* b = new char[datas[6].length()+1];
		strcpy(r, datas[4].c_str());
		strcpy(g, datas[5].c_str());
		strcpy(b, datas[6].c_str());
		r[datas[4].length()] = '\0';
		g[datas[5].length()] = '\0';
		b[datas[6].length()] = '\0';
		RGB rgb = {r[0], g[0],b[0]};
		int dash = stoi(datas[7]);
		int thick = stoi(datas[8]);
		line->setRGB(rgb);
    		line->setDash(dash);
    		line->setThickness(thick);
    		lines.push_back(line);
		delete [] r; delete [] g; delete [] b;
	
	}
	fin.close();
	return lines;
}

vector<Polygon*> load_polygons(char* filename) {
	vector<Polygon*> polygons;
	ifstream fin(filename);
	string data;
	while(getline(fin,data)){

		Polygon* polygon = new Polygon;
		vector<string> points_string;
		points_string = split(data,"|");
		for (vector<string>::iterator it = points_string.begin(); it != points_string.end(); it++) {
			char* info;
			string idx = (*it);
			char* writable = new char[idx.length()+1];
			strcpy(writable, idx.c_str());
			writable[idx.length()] = '\0';
			info = strtok(writable,",\n");
			vector<string> xy;
			while(info!=NULL) {
				xy.push_back(string(info));
				info = strtok(NULL,",\n");
			}
			Point* point = new Point(stoi(xy[0]),stoi(xy[1]));
			polygon->addPoint(point);
			delete [] writable;
		} 
		polygons.push_back(polygon);
	}	
	
	fin.close();
	return polygons;
}

vector<string> split(string str, string tok){

	vector<string> res;
	while (str.size()){
		int idx = str.find(tok);
		if(idx!=string::npos) {
			res.push_back(str.substr(0,idx));
			str = str.substr(idx+tok.size());
			if(str.size()==0) 
				{res.push_back(str);}
			else 
				{res.push_back(str); str = "";}
		} 
	}
	return res;
}
