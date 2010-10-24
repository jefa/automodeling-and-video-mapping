#ifndef __Material_h__
#define __Material_h__

#include <string>
using namespace std;

#include "IPropertyManager.h"

enum A_PARAM_MATERIAL
{
    DIFFUSE_R, DIFFUSE_G, DIFFUSE_B,
    AMBIENT_R, AMBIENT_G, AMBIENT_B,
};

class Material : public IPropertyManager
{
	public:
        Material();
        virtual ~Material();
        void set(int aParam, float value);
        float get(int aParam);
        void enable();
        void disable();

	private:
        float diffuse[3];
        float ambient[3];

};

#endif
