#include <string>
#include <vector>
#include <exception>

using namespace std;

#include "Object3D.h"

void Object3D::clone() {
	throw "Not yet implemented";
}

void Object3D::setPosX(float param)
{
    this->_x = param;
}

float Object3D::getPosX()
{
    return this->_x;
}

void Object3D::setPosY(float param)
{
    this->_y = param;
}

float Object3D::getPosY()
{
    return this->_y;
}

void Object3D::setPosZ(float param)
{
    this->_z = param;
}

float Object3D::getPosZ()
{
    return this->_z;
}

void Object3D::addObject(ofx3DModelLoader *obj3d)
{
    this->obj3dModel = obj3d;

}

void Object3D::addObject(string path3dObj)
{
    if (this->obj3dModel == NULL)
    {
        this->obj3dModel = new ofx3DModelLoader();

    }
    this->obj3dModel->loadModel(path3dObj, 20);
}

void Object3D::draw()
{
    this->obj3dModel->draw();
}

void Object3D::addModifier(Modifier *m)
{
    this->modifiers.push_back(m);
}
