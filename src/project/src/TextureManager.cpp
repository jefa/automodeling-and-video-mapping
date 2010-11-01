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
    imageTextures.insert(pair<string, ofImage*>(key, image));
}

void TextureManager::LoadVideoTexture(string key, string path) {
    ofxAlphaVideoPlayer *video = new ofxAlphaVideoPlayer();
    video->loadMovie(path);
    videoTextures.insert(pair<string, ofxAlphaVideoPlayer*>(key, video));
}

void TextureManager::UnloadVideoTexture(string key) {
    videoTextures.erase(key);
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
        ofImage *image = imageTextures[key];
        image->update();
        return image->getTextureReference();
    }
    else if (type == videoTexture) {
        ofxAlphaVideoPlayer *vid = videoTextures[key];
        vid->draw(0,0,0,0); //HACK: la textura se actualiza con este draw
        return vid->getTextureReference();
    }
}
