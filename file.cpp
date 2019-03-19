#include "file.h"
#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

void save_lines(vector<Line* > *lines, char * filename) {

    ofstream fout(filename, ios_base::out | ios_base::binary);
    
    for (vector<Line *>::iterator it = (*lines).begin(); it != (*lines).end(); it++){
		RGB rgb = (*it)->getRGB();
		int dash = (*it)->getDash();
		int thickness = (*it)->getThickness();

        fout << (*it)->getP1()->getX() << ',' << (*it)->getP1()->getY() << '|' << (*it)->getP2()->getX() << ',' << (*it)->getP2()->getY() << '|' << rgb.r << ',' << rgb.g << ',' << rgb.b << '|' << dash << '|' << thickness << endl;
    }

    fout.close();
}

void save_polygons(vector<Polygon* > *polygons, char * filename) {
    struct RGB rgb;

    ofstream fout(filename);
    for (vector<Polygon *>::iterator it = (*polygons).begin(); it != (*polygons).end(); it++) {

        vector <Point*> pts = (*it)->getPointVector();
        for (vector<Point *>::iterator it2 = pts.begin(); it2 != pts.end(); it2++) {
            fout << (*it2)->getX() << ',' << (*it2)->getY();
	    fout << '|';
        }
        rgb = (*it)->getRGB();
	    fout << endl << rgb.r << endl << rgb.g << endl << rgb.b << endl;
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
    struct RGB rgb {0,0,0};
	while(getline(fin,data)){
		Polygon* polygon = new Polygon(rgb);
		vector<string> points_string;

        points_string = split(data,"|");
		while (points_string.size() > 1) {
			char* info;
			string idx = *(points_string.begin());
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

            points_string = split(*(points_string.end()-1),"|");
		}

        getline(fin,data);
        rgb.r = data.c_str()[0];
        getline(fin,data);
        rgb.g = data.c_str()[0];
        getline(fin,data);
        rgb.b = data.c_str()[0];
        polygon->setRGB(rgb);
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
