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
        static void Init();
        static void LoadImageTexture(string key, string path);
        static void LoadVideoTexture(string key, string path);
        static void UnloadVideoTexture(string key);
        static void PlayVideo(string key);
        static void StopVideo(string key);
        static bool IsTextureReady(string key, textureType type);
        static ofTexture& GetTextureReference(string key, textureType type);
        static void Update();
    protected:
    private:
        static map<string, ofImage*> imageTextures;
        static map<string, ofxAlphaVideoPlayer*> videoTextures;
        static ofTexture defaultTexture;
};

#endif // TEXTUREMANAGER_H
