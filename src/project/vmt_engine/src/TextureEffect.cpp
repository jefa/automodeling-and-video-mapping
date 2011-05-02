#include "TextureEffect.h"

TextureEffect::TextureEffect(string id, QuadGroup *qg, string texturePath, textureType type) {
    switch(type) {
        case VIDEO_TEXTURE:
            TextureManager::LoadVideoTexture(texturePath, texturePath);
            TextureManager::PlayVideo(texturePath, 1);
            break;
        case IMAGE_TEXTURE:
            TextureManager::LoadImageTexture(texturePath, texturePath);
            break;
    }
    this->id = id;
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

int TextureEffect::getType(){
    return TEXTURE_EFFECT;
}

QuadGroup* TextureEffect::getGroup(){
    return this->group;
}

Object3D* TextureEffect::getObject3D(){
    return this->object3d;
}

string TextureEffect::getFacesID(){
    return this->facesID;
}

string TextureEffect::getTextureKey(){
    return this->textureKey;
}

textureType TextureEffect::getTextureType(){
    return this->type;
}

bool TextureEffect::getIsGroup(){
    return this->isGroup;
}


const char* TextureEffect::toString(){
    string txt = this->id + " : TextureEffect : ";//+facesID+"::"+textureKey+"::"+isGroup+"::";
    if (isGroup){
        txt = txt+ group->getName();
    } else {
        txt = txt+ object3d->getId();
    }
    return txt.c_str();
}

SerializedNode* TextureEffect::Serialize() {
    SerializedNode *node = new SerializedNode("effect");
    node->addAttribute("id", this->id);

    node->addAttribute("texturename", this->textureKey);

    if(this->isGroup) {
        node->addAttribute("type", "grouptexture");
        node->addAttribute("groupid", this->group->getName());
    }
    else {
        node->addAttribute("type", "object3dtexture");
        node->addAttribute("objid", this->object3d->getId());
        node->addAttribute("facesid", this->facesID);
        node->addAttribute("texturename", this->textureKey);
    }

    return node;
}
