#include "Background.h"
#include "ofMain.h"

#include <string>
using namespace std;

Background::Background()
{
    //ctor
    color.r = color.g = color.b = 0;
}

void Background::set(string aParam, float value) {
    if(aParam.compare("color.r") == 0) {
        color.r = value;
    }
    else if(aParam.compare("color.g") == 0) {
        color.g = value;
    }
    else if(aParam.compare("color.b") == 0) {
        color.b = value;
    }
    ofBackground(color.r, color.g, color.b);
}

float Background::get(string aParam) {
    if(aParam.compare("color.r") == 0) {
        return color.r;
    }
    else if(aParam.compare("color.g") == 0) {
        return color.g;
    }
    else if(aParam.compare("color.b") == 0) {
        return color.b;
    }
}

Background::~Background()
{
    //dtor
}
