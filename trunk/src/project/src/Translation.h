#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __Translation_h__
#define __Translation_h__

#include "Modifier.h"
#include "PropertyManager.h"

class Translation: public Modifier, public IPropertyManager
{
	private:
        string _x;
        string _y;
        string _z;

	public:
        float get(string aParam);
        void set(string aParam, float aValue);
};

#endif
