#include <unistd.h>
#include <fstream>
#include <string>
#include "objects.h"
using namespace std;

void save_lines(vector<Line*> lines);

void save_polygons(vector<Polygon*> polygons);



int main(int argc, char** argv){

    vector<Line* > lines;
    vector<Polygon* > polygons;

    lines.push_back(new Line(new Point(100,100),new Point(200,200)));
    lines.push_back(new Line(new Point(1,1),new Point(2,2)));

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

    return 0;
}




void save_lines(vector<Line* > lines) {

    ofstream file;
    file.open("lines.txt");
    
    for (vector<Line *>::iterator it = lines.begin(); it != lines.end(); it++){
        Point *P1 = (*it)->getP1();
        Point *P2 = (*it)->getP2();

        file << P1->getX() << ',' << P1->getY() << '|' << P2->getX() << ',' << P2->getY() << endl;
    }

    file.close();
}

void save_polygons(vector<Polygon* > polygons) {

    ofstream fout("polygons.txt");
    for (vector<Polygon *>::iterator it = polygons.begin(); it != polygons.end(); it++) {

        vector <Point*> pts = (*it)->getPointVector();
        for (vector<Point *>::iterator it2 = pts.begin(); it2 != pts.end(); it2++) {
            fout << (*it2)->getX() << "," << (*it2)->getY() << endl;
        }
        fout << endl;
    }
    fout.close();
}
