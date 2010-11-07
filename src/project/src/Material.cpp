#include "Material.h"
#include "ofMain.h"

Material::Material(){
    ambient[0] = 1.0f;//ofRandomuf();
    ambient[1] = 1.0f;//ofRandomuf();
    ambient[2] = 1.0f;//ofRandomuf();
    ambient[3] = 1;

    texture_shader.loadShader("shaders/texture_ambient");

    this->texID = "";
}

Material::~Material(){
}

void Material::SetTextureParams(string id, textureType type, int textureUnit) {
    this->texID = id;
    this->texType = type;
    this->textureUnit = textureUnit;
}

void Material::Enable(){
    bool isTexReady;
    if(this->texID.compare("") == 0 )
        isTexReady = false;
    else {
        isTexReady = TextureManager::IsTextureReady(texID, texType);
    }
    if(isTexReady) {
        ofTexture &tex = TextureManager::GetTextureReference(texID, texType);

        glEnable(GL_TEXTURE_2D);
        glActiveTextureARB(GL_TEXTURE0_ARB + textureUnit);

        glBindTexture(GL_TEXTURE_2D, tex.texData.textureID);

        texture_shader.setShaderActive(true);
        texture_shader.setUniformVariable2f("texSize", tex.getWidth(), tex.getHeight());
        texture_shader.setUniformVariable3f("color", ambient[0], ambient[1], ambient[2]);
        texture_shader.setUniformVariable1i("tex", textureUnit);
    }
    else {
        glColor3f(0, 0, 1);
    }
}

void Material::Disable() {
	//glActiveTextureARB(GL_TEXTURE0_ARB + textureUnit);
    //glBindTexture(GL_TEXTURE_2D, NULL);
	texture_shader.setShaderActive(false);
	//glDisable(GL_TEXTURE_2D);
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

