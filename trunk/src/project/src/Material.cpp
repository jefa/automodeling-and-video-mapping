#include "Material.h"
#include "ofMain.h"

Material::Material(){
    ambient[0] = ofRandomuf();
    ambient[1] = ofRandomuf();
    ambient[2] = ofRandomuf();
    ambient[3] = 1;

    texture_shader.loadShader("shaders/texture_ambient");
}

Material::~Material(){
}

void Material::SetTextureParams(string id, textureType type) {
    this->texID = id;
    this->texType = type;
}

void Material::Enable(){
    ofTexture &tex = TextureManager::GetTextureReference(texID, texType);
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glBindTexture(GL_TEXTURE_2D, tex.texData.textureID);

    texture_shader.setShaderActive(true);
    texture_shader.setUniformVariable2f("texSize", tex.getWidth(), tex.getHeight());
    texture_shader.setUniformVariable3f("color", ambient[0], ambient[1], ambient[2]);
}

void Material::Disable() {
	texture_shader.setShaderActive(false);
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

