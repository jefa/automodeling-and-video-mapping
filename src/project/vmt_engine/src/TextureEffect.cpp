#include "TextureEffect.h"

TextureEffect::TextureEffect(QuadGroup *qg, string textureKey, string texturePath, textureType type)
{
    switch(type) {
        case VIDEO_TEXTURE:
            TextureManager::LoadVideoTexture(textureKey, texturePath);
            TextureManager::PlayVideo(textureKey, 1);
            break;
        case IMAGE_TEXTURE:
            TextureManager::LoadImageTexture(textureKey, texturePath);
            break;
    }
    this->group = qg;
    this->textureKey = textureKey;
    this->type = type;
}

TextureEffect::~TextureEffect()
{
    //dtor
}

void TextureEffect::play() {
}

void TextureEffect::test() {
    this->group->SetTextureParams(this->textureKey, this->type);
}
