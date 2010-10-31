#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "ofImage.h"
#include "../addons/ofxAlphaVideoPlayer/ofxAlphaVideoPlayer.h"

#include <map>
using namespace std;

enum textureType {imageTexture, videoTexture};

class TextureManager
{
    public:
        TextureManager();
        virtual ~TextureManager();
        static void LoadImageTexture(string key, string path);
        static void LoadVideoTexture(string key, string path);
        static ofTexture& GetTextureReference(string key, textureType type);
    protected:
    private:
        static map<string, ofImage*> imageTextures;
        static map<string, ofxAlphaVideoPlayer*> videoTextures;
};

#endif // TEXTUREMANAGER_H
