#include <unistd.h>
#include <fstream>
#include <string>
#include "objects.h"
using namespace std;

void save_lines(vector<Line&> lines);

void save_polygons(vector<Polygon&> polygons);



int main(int argc, char** argv){

    vector<Line> lines;
    vector<Polygon> polygons;

    Line line(new Point(100,100), new Point(100,100));
    lines.push_back(line);

    // Polygon polygon;

    // polygon.addPoint(new Point(100,100));
    // polygon.addPoint(new Point(200,200));
    // polygon.addPoint(new Point(300,300));

    // polygon.render(fbp,vinfo,finfo);

    save_lines(lines);

    return 0;
}




void save_lines(vector<Line&> lines) {

    ofstream fout("lines.txt");
    for(int i=0;i<lines.size();i++) {

        Point p1 = lines[i].getP1();
        Point p2 = lines[i].getP2();

        fout << p1.getX() << " " << p1.getY() << " " << p2.getX() << " " << p2.getY() << endl;
    }
    fout.close();
}

void save_polygons(vector<Polygon&> polygons) {

    ofstream fout("polygons.txt");
    for(int i=0;i<polygons.size();i++) {

        vector <Point*> pts = polygons[i].getPointVector();
        for(int i=0;i<pts.size();i++) {
            fout << pts[i].getX() << " " << pts[i].getY() << endl;
        }
        fout << endl;
    }
    fout.close();
}
