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

enum A_PARAM_OBJECT3D {POS_X, POS_Y, POS_Z};

class Object3D : public Clonable, public IPropertyManager
{
    private:
        vector<Modifier*> modifiers;
		vector<ofx3DModelLoader*> obj3dModels;

	public:
        virtual float get(int aParam);
        virtual void set(int aParam, float aValue);

        void clone();
        void addModifier(Modifier *m);
        void addObject(string );
        void draw();

};

#endif
