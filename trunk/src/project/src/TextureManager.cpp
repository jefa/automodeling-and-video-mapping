#include "TextureManager.h"

map<string, ofImage*> TextureManager::imageTextures;
map<string, ofxAlphaVideoPlayer*> TextureManager::videoTextures;

TextureManager::TextureManager() {
    //ctor
}

TextureManager::~TextureManager() {
    //dtor
}

void TextureManager::LoadImageTexture(string key, string path) {
    ofImage * image = new ofImage();
    image->loadImage(path);
    imageTextures.insert(make_pair(key, image));
}

void TextureManager::LoadVideoTexture(string key, string path) {
    ofxAlphaVideoPlayer *video = new ofxAlphaVideoPlayer();
    video->loadMovie(path);
    videoTextures.insert(make_pair(key, video));
}

void TextureManager::Update() {
    map<string, ofxAlphaVideoPlayer*>::iterator it;
    for(it = videoTextures.begin(); it != videoTextures.end(); ++it) {
        (*it).second->idleMovie();
    }
}

void TextureManager::PlayVideo(string key) {
    videoTextures[key]->play();
}

ofTexture& TextureManager::GetTextureReference(string key, textureType type) {
    if(type == imageTexture) {
        return imageTextures[key]->getTextureReference();
    }
    else if (type == videoTexture) {
        return videoTextures[key]->getTextureReference();
    }
}
