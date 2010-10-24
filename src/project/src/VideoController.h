#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include "../addons/ofxAlphaVideoPlayer/ofxAlphaVideoPlayer.h"

#include <string>
#include <map>
using namespace std;

class VideoController
{
    public:
        VideoController();
        virtual ~VideoController();
        void AddVideo(string id, string path);
        void PlayVideo(string id);
        void IdleMovies();
        void bindTexture(string id);
        void unbindTexture(string id);
    protected:
    private:
        std::map<std::string, ofxAlphaVideoPlayer*> videos;
};

#endif // VIDEOCONTROLLER_H
