#include "Material.h"
#include "ofMain.h"

Material::Material(){
    ambient[0] = ofRandomuf();
    ambient[1] = ofRandomuf();
    ambient[2] = ofRandomuf();
    ambient[3] = 1;

    image = new ofImage();
    image->loadImage("pegado.jpg");

    ambient_shader.loadShader("shaders/texture_ambient");
}

Material::~Material(){
}

void Material::Enable(){
    ofTexture &tex = image->getTextureReference();
    int textureID = tex.texData.textureID;

    glActiveTextureARB(GL_TEXTURE0_ARB);
    glBindTexture(GL_TEXTURE_2D, textureID);

    ambient_shader.setShaderActive(true);
    ambient_shader.setUniformVariable2f("texSize", tex.getWidth(), tex.getHeight());
    ambient_shader.setUniformVariable3f("color", ambient[0], ambient[1], ambient[2]);
}

void Material::Disable() {
	ambient_shader.setShaderActive(false);
}

float Material::get(int aParam) {
    switch(aParam) {
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

