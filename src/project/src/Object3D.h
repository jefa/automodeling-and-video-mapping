#ifndef __Object3D_h__
#define __Object3D_h__

#include "Modifier.h"
#include "Clonable.h"
#include "ofx3DModelLoader.h"

#include <string>
using namespace std;

class Modifier;
class Object3D;

class Object3D : public Clonable
{
    private:
        vector<Modifier> modifiers;
		ofx3DModelLoader obj3dModel;


	public:
        void clone();
        void addModifier(Modifier *m);
        //void addObject();
};

#endif
