#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __Translation_h__
#define __Translation_h__

#include "Modifier.h"
#include "IPropertyManager.h"

class Translation: public Modifier, public IPropertyManager
{
	private:
        string _x;
        string _y;
        string _z;

	public:
        Translation() : Modifier() {};
        Translation(Object3D *objRef) : Modifier( objRef ) {};
        float get(string aParam);
        void set(string aParam, float aValue);
};

#endif
