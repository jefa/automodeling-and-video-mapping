#include "Material.h"
#include "ofMain.h"

Material::Material(){
    MaterialController::Init();

    ambient[0] = ofRandomuf();
    ambient[1] = ofRandomuf();
    ambient[2] = ofRandomuf();

    image = new ofImage();
    image->loadImage("peg2.jpg");
}

Material::~Material(){
}

void Material::Enable(){
    MaterialController::EnableShader(AMBIENT_SHADER);

    int textureID = image->getTextureReference().texData.textureID;

    glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Material::Disable() {
    glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);
	MaterialController::DisableShader();
}

float Material::get(int aParam) {
    switch(aParam)
    {
        case AMBIENT_R:
            return ambient[0];
        case AMBIENT_G:
            return ambient[1];
        case AMBIENT_B:
            return ambient[2];
    }
	return 0;
}

void Material::set(int aParam, float value) {
    switch(aParam)
    {
        case AMBIENT_R:
            ambient[0] = value;
            break;
        case AMBIENT_G:
            ambient[1] = value;
            break;
        case AMBIENT_B:
            ambient[2] = value;
            break;
    }
}

