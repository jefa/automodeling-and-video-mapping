#include "Material.h"
#include "ofMain.h"

Material::Material(){
    diffuse[0] = ofRandomuf();
    diffuse[1] = ofRandomuf();
    diffuse[2] = ofRandomuf();

    ambient[0] = ofRandomuf();
    ambient[1] = ofRandomuf();
    ambient[2] = ofRandomuf();
}

Material::~Material(){
}

void Material::enable(){
    if(glIsEnabled(GL_LIGHTING)){
        const GLfloat matOne[4]={1,1,1,1};
        /*if(hasTextureMap){ //replace color with texture, but keep lighting contribution
            glMaterialfv(materialFaces, GL_DIFFUSE, matOne);
        }
        else glMaterialfv(materialFaces, GL_DIFFUSE, currentMaterial.getDiffuseColor());
        glMaterialfv(materialFaces, GL_AMBIENT, currentMaterial.getAmbientColor());*/
    }
    else {
        glColor3fv(diffuse);
    }
}

void Material::disable() {
    //No hace nada por ahora
}

float Material::get(int aParam) {
    switch(aParam)
    {
        case DIFFUSE_R:
            return diffuse[0];
        case DIFFUSE_G:
            return diffuse[1];
        case DIFFUSE_B:
            return diffuse[2];
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
        case DIFFUSE_R:
            diffuse[0] = value;
            break;
        case DIFFUSE_G:
            diffuse[1] = value;
            break;
        case DIFFUSE_B:
            diffuse[2] = value;
            break;
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

