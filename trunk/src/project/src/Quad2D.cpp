#include "Quad2D.h"

Quad2D::Quad2D(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4);
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}

Quad2D::~Quad2D()
{
    //dtor
}

void Quad2D::draw()
{
    ofVertex(p1.x, p1.y);
    ofVertex(p2.x, p2.y);
    ofVertex(p3.x, p3.y);
    ofVertex(p4.x, p4.y);
}

void Quad2D::set(int aParam, float value)
{

}

float Quad2D::get(int aParam)
{
    return 0;
}
