#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __PropertyManager_h__
#define __PropertyManager_h__

class IPropertyManager
{
	public:

	virtual void set(string aParam, float value) = 0;
    virtual float get(string aParam) = 0;

};

#endif
