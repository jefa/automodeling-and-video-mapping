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
        float _x;
        float _y;
        float _z;
        vector<Modifier*> modifiers;
		ofx3DModelLoader *obj3dModel;

	public:
        void setPosX(float);
        float getPosX();
        void setPosY(float);
        float getPosY();
        void setPosZ(float);
        float getPosZ();

        void clone();
        void addModifier(Modifier *m);
        void addObject(ofx3DModelLoader *obj3d);
        void addObject(string );
        void draw();

};

#endif
