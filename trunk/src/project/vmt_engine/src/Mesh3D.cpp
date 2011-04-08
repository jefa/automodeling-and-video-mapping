#include "Mesh3D.h"

Mesh3D::Mesh3D(string path)
{
    //ctor
    model.loadModel(path, 30);
}

Mesh3D::~Mesh3D()
{
    //dtor
}

void Mesh3D::draw() {
    model.draw();
}
