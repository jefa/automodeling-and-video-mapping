#include <string>
#include <vector>
#include <exception>

using namespace std;

#include "Object3D.h"

ofx3DModelLoader *obj3d_1;

void Object3D::clone() {
	throw "Not yet implemented";
}

void Object3D::setPosX(float param)
{
    this->_x = param;
    obj3d_1->setPosition(param, 1, 1);
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



void Object3D::addObject(string path3dObj)
{
    ofx3DModelLoader *obj3d = new ofx3DModelLoader();
    obj3d_1 = obj3d;
    obj3d->loadModel(path3dObj, 20);
    this->obj3dModels.push_back(obj3d);
}

void Object3D::draw()
{
    vector<ofx3DModelLoader*>::iterator it;
    for ( it=obj3dModels.begin() ; it < obj3dModels.end(); it++ )
    {
        //((ofx3DModelLoader)*it)->obj3dModel->draw();
        ofx3DModelLoader *obj = (ofx3DModelLoader*) *it;
        obj->draw();
    }
}

void Object3D::addModifier(Modifier *m)
{
    this->modifiers.push_back(m);
}

float Object3D::get(string aParam) {
    if (aParam.compare("x") == 0)
    {
        return getPosX();

    } else if (aParam.compare("y") == 0)
    {
        return getPosY();

    } else if (aParam.compare("z") == 0)
    {
        return getPosZ();
    }
    return 0;
}

void Object3D::set(string aParam, float aValue) {
    if (aParam.compare("x") == 0)
    {
        setPosX(aValue);

    } else if (aParam.compare("y") == 0)
    {
        setPosY(aValue);

    } else if (aParam.compare("z") == 0)
    {
        setPosZ(aValue);
    }
}

