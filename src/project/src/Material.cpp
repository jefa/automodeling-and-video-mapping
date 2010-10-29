#include "Material.h"
#include "ofMain.h"

Material::Material(){
    MaterialController::Init();

    ambient[0] = ofRandomuf();
    ambient[1] = ofRandomuf();
    ambient[2] = ofRandomuf();

    image = new ofImage();
    image->loadImage("pegado.jpg");
}

Material::~Material(){
}

void Material::Enable(){
    int textureID = image->getTextureReference().texData.textureID;

    //image->draw(50,50,100,100);

    //image->getTextureReference().draw(0,0);
    //glActiveTextureARB(GL_TEXTURE0_ARB);
    //glActiveTexture(GL_TEXTURE0);

    //MaterialController::EnableShader(AMBIENT_SHADER);

    //image->getTextureReference().bind();
    //glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textureID);

    ofTexture &tex = image->getTextureReference();

    tex.bind();

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    //glLoadIdentity();

    ofTextureData texData = tex.texData;// getTextureData();
    if(texData.textureTarget == GL_TEXTURE_RECTANGLE_ARB) {
        glScalef(tex.getWidth(), tex.getHeight(), 1.0f);
        //ofLog(OF_LOG_NOTICE, "RECTANGULO! ES UN RECTANGULO!");
    } else {
        glScalef(tex.getWidth() / texData.tex_w, tex.getHeight() / texData.tex_h, 1.0f);
    }

    glMatrixMode(GL_MODELVIEW);

}

void Material::Disable() {


    //glActiveTextureARB(GL_TEXTURE0_ARB);
    //glActiveTexture(GL_TEXTURE0);
    //image->getTextureReference().unbind();
	//glDisable(GL_TEXTURE);
	//glDisable(GL_TEXTURE_2D);

	//MaterialController::DisableShader();

    image->getTextureReference().unbind();
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
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

