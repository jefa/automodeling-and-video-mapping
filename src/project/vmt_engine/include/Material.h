#ifndef __Material_h__
#define __Material_h__

#include "TextureManager.h"

#include "../addons/ofxShader/ofxShader.h"
#include "ofImage.h"

#include <string>
using namespace std;

enum A_PARAM_MATERIAL
{
    AMBIENT_R, AMBIENT_G, AMBIENT_B, AMBIENT_A
};

class Material
{
	public:
        Material();
        virtual ~Material();
        void set(int aParam, float value);
        float get(int aParam);
        void Enable();
        void Disable();

        void SetTextureParams(string id, textureType type, int textureUnit);

	private:
        float ambient[4];
        ofxShader texture_shader;

        string texID;
        textureType texType;
        int textureUnit;

};

#endif
