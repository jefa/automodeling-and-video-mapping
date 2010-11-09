#include "Material.h"
#include "ofMain.h"

Material::Material(){
    ambient[0] = 1.0f;//ofRandomuf();
    ambient[1] = 1.0f;//ofRandomuf();
    ambient[2] = 1.0f;//ofRandomuf();
    ambient[3] = 1.0f;

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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(tex.texData.textureTarget, (GLuint)tex.texData.textureID);

        texture_shader.setShaderActive(true);

        int texwidth = tex.getWidth();
        int texheight = tex.getHeight();
        float texwidthpow2 = ofNextPow2(texwidth);
        float texheightpow2 = ofNextPow2(texheight);

        texture_shader.setUniformVariable2f("texCorrection", texwidth / texwidthpow2, texheight / texheightpow2);
        texture_shader.setUniformVariable4f("color", ambient[0], ambient[1], ambient[2], ambient[3]);
        texture_shader.setUniformVariable1i("tex", GL_TEXTURE0 + textureUnit);
    }
    else {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4fv(ambient);
    }
}

void Material::Disable() {
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
        case AMBIENT_A:
            return ambient[3];
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
        case AMBIENT_A:
            ambient[3] = value;
            break;
    }
}

