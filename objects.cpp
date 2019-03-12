#include <cstdlib>
#include <iostream>
#include "objects.h"
using namespace std;

// **** POINT CLASS ****

Point::Point(int x, int y){
    this->x = x;
    this->y = y;
}
Point::~Point(){
    cout << "Point destructor" << endl;
}

int Point::getX(){
    return x;
}
int Point::getY(){
    return y;
}
void Point::setX(int x){
    this->x = x;
}
void Point::setY(int y){
    this->y = y;
}

// **** LINE CLASS ****
Line::Line(Point * P1, Point * P2) : Object(){
    this->P1 = P1;
    this->P2 = P2;
}
Line::~Line(){
    (*P1).~Point();
    (*P2).~Point();
    cout << "Line destructor" << endl;
}
        
Point Line::getP1(){
    return *P1;
}
Point Line::getP2(){
    return *P2;
}
void Line::setP1(Point* P1){
    (*P1).~Point();
    this->P1 = P1;
}
void Line::setP2(Point* P2){
    (*P2).~Point();
    this->P2 = P2;
}
        
void Line::render(char* fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    cout << "Point 1: " << (*P1).getX() << "," << (*P1).getY() << endl;
    cout << "Point 2: " << (*P2).getX() << "," << (*P2).getY() << endl;
}