#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __Material_h__
#define __Material_h__

#include "IPropertyManager.h"

class Material : public IPropertyManager
{
	private:
        string _shaderDer;
        string* _texture;

	public:
        void set(string aParam, float value) = 0;
        float get(string aParam) = 0;

};

#endif
