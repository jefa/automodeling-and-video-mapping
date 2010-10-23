#include "Background.h"
#include "ofMain.h"

#include <string>
using namespace std;

Background::Background()
{
    //ctor
    color.r = color.g = color.b = 0;
}

void Background::set(int aParam, float value) {
    switch(aParam)
    {
        case COLOR_R:
            color.r = value;
            break;
        case COLOR_G:
            color.g = value;
            break;
        case COLOR_B:
            color.b = value;
            break;
    }
    ofBackground(color.r, color.g, color.b);
}

float Background::get(int aParam) {
    switch(aParam)
    {
        case COLOR_R:
            return color.r;
        case COLOR_G:
            return color.g;
        case COLOR_B:
            return color.b;
    }
}

Background::~Background()
{
    //dtor
}
