#include "TextureEffect.h"

TextureEffect::TextureEffect(QuadGroup *qg, string texturePath, textureType type) {
    switch(type) {
        case VIDEO_TEXTURE:
            TextureManager::LoadVideoTexture(texturePath, texturePath);
            TextureManager::PlayVideo(texturePath, 1);
            break;
        case IMAGE_TEXTURE:
            TextureManager::LoadImageTexture(texturePath, texturePath);
            break;
    }
    this->group = qg;
    this->textureKey = texturePath;
    this->type = type;
    this->isGroup = true;
}

TextureEffect::TextureEffect(Object3D *obj3d, string facesID, string texturePath, textureType type) {
    switch(type) {
        case VIDEO_TEXTURE:
            TextureManager::LoadVideoTexture(texturePath, texturePath);
            TextureManager::PlayVideo(texturePath, 1);
            break;
        case IMAGE_TEXTURE:
            TextureManager::LoadImageTexture(texturePath, texturePath);
            break;
    }

    this->object3d = obj3d;
    this->facesID = facesID;

    this->textureKey = texturePath;
    this->type = type;
    this->isGroup = false;
}

TextureEffect::~TextureEffect()
{
    //dtor
}

void TextureEffect::play() {
}

void TextureEffect::test() {
    if(isGroup)
        this->group->SetTextureParams(this->textureKey, this->type);
    else {
        this->object3d->SetTextureParamsForMaterial(this->facesID, this->textureKey, this->type);
    }
}
