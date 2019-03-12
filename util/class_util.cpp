#include <iostream>
#include "class_util.h"
using namespace std;

Object::Object() { };
Object::~Object() {
    cout << "Object destructor" << endl;
};