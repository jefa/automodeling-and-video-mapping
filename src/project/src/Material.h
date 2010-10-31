#ifndef __Material_h__
#define __Material_h__

#include "IPropertyManager.h"
#include "TextureManager.h"

#include "ofxShader.h"

#include "ofImage.h"

#include <string>
using namespace std;

enum A_PARAM_MATERIAL
{
    AMBIENT_R, AMBIENT_G, AMBIENT_B,
};

class Material : public IPropertyManager
{
	public:
        Material();
        virtual ~Material();
        void set(int aParam, float value);
        float get(int aParam);
        void Enable();
        void Disable();

        void SetTextureParams(string id, textureType type);

	private:
        float ambient[4];
        ofxShader texture_shader;

        string texID;
        textureType texType;

};

#endif
