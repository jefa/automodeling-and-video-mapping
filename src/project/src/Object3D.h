#ifndef __Object3D_h__
#define __Object3D_h__

#include "Modifier.h"
#include "Clonable.h"
#include "ofx3DModelLoader.h"
#include "IPropertyManager.h"

#include <string>
using namespace std;

class Modifier;
class Object3D;

class Object3D : public Clonable, public IPropertyManager
{
    private:
        vector<Modifier*> modifiers;
		vector<ofx3DModelLoader*> obj3dModels;

	public:
        void setPosX(float);
        float getPosX();
        void setPosY(float);
        float getPosY();
        void setPosZ(float);
        float getPosZ();

        float get(string aParam);
        void set(string aParam, float aValue);

        void clone();
        void addModifier(Modifier *m);
        void addObject(string );
        void draw();

};

#endif
