#ifndef __Modifier_h__
#define __Modifier_h__

#include "Object3D.h"

class Object3D;

#include <string>
#include <vector>
#include <exception>

using namespace std;

class Modifier
{
	protected:
        string _id;
        string _gizmo;
        string _center;
        string _vecX;
        string _vecY;
        string _vecZ;
        Object3D* objRef;

	public:
        Modifier();
        Modifier(Object3D *objRef);
        ~Modifier();
        void getGizmo();
};

#endif
