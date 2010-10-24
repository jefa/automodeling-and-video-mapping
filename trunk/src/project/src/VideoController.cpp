#include "VideoController.h"

VideoController::VideoController()
{
    //ctor
}

VideoController::~VideoController()
{
    //dtor
}

void VideoController::AddVideo(string id, string path)
{
    ofxAlphaVideoPlayer *video = new ofxAlphaVideoPlayer();
    video->loadMovie(path);
    videos.insert(make_pair(id, video));
}

void VideoController::IdleMovies()
{
    map<string, ofxAlphaVideoPlayer*>::const_iterator end = videos.end();
    for (map<string, ofxAlphaVideoPlayer*>::const_iterator it = videos.begin(); it != end; ++it)
    {
        it->second->idleMovie();
    }
}

void VideoController::PlayVideo(string id)
{
    videos[id]->play();
}

void VideoController::bindTexture(string id) {
    ofxAlphaVideoPlayer* ofvp = videos[id];

    ofTexture &tex = ofvp->getTextureReference();
    tex.bind();

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    ofTextureData texData = tex.getTextureData();
    if(texData.textureTarget == GL_TEXTURE_RECTANGLE_ARB) {
        glScalef(tex.getWidth(), tex.getHeight(), 1.0f);
    } else {
        glScalef(tex.getWidth() / texData.tex_w, tex.getHeight() / texData.tex_h, 1.0f);
    }

    glMatrixMode(GL_MODELVIEW);
}

void VideoController::unbindTexture(string id) {
    ofxAlphaVideoPlayer* ofvp = videos[id];

    ofvp->getTextureReference().unbind();
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
