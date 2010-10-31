#include "TextureManager.h"

map<string, ofImage*> TextureManager::imageTextures;
map<string, ofxAlphaVideoPlayer*> TextureManager::videoTextures;

TextureManager::TextureManager()
{
    //ctor
}

TextureManager::~TextureManager()
{
    //dtor
}

void TextureManager::LoadImageTexture(string key, string path) {
    ofImage * image = new ofImage();
    image->loadImage(path);
    imageTextures.insert(pair<string, ofImage*>(key, image));
}

void TextureManager::LoadVideoTexture(string key, string path) {
}

ofTexture& TextureManager::GetTextureReference(string key, textureType type) {
    if(type == imageTexture) {
        return imageTextures[key]->getTextureReference();
    }
    else if (type == videoTexture) {
        return videoTextures[key]->getTextureReference();
    }
}
