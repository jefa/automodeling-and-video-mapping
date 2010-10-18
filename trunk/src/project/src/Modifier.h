#ifndef __Modifier_h__
#define __Modifier_h__

//#include "Object3D.h"

#include <string>
#include <vector>
#include <exception>

using namespace std;

class Modifier
{
	private:
        string _id;
        string _gizmo;
        string _center;
        string _vecX;
        string _vecY;
        string _vecZ;
        //Object3D* _unnamed_Object3D_;

	public:
        Modifier();
        ~Modifier();
        void getGizmo();
};

#endif
