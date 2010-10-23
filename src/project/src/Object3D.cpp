#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Object3D.h"

ofx3DModelLoader *obj3d_1;

void Object3D::clone() {
	throw "Not yet implemented";
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

float Object3D::get(int aParam) {
    switch(aParam)
    {
        case POS_X:
            return obj3d_1->pos.x;
        case POS_Y:
            return obj3d_1->pos.y;
        case POS_Z:
            return obj3d_1->pos.z;
    }
    return 0;
}

void Object3D::set(int aParam, float aValue) {
    switch(aParam)
    {
        case POS_X:
            obj3d_1->pos.x = aValue;
            break;
        case POS_Y:
            obj3d_1->pos.y = aValue;
            break;
        case POS_Z:
            obj3d_1->pos.z = aValue;
            break;
    }
}

