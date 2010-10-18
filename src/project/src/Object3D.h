#ifndef __Object3D_h__
#define __Object3D_h__

#include "Modifier.h"
#include "Clonable.h"

#include <string>
using namespace std;

class Object3D : public Clonable
{
    private:
        vector<Modifier> modifiers;
        //Modifier* _n;

	public:
        void clone();
};

#endif
