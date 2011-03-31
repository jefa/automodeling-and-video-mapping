#ifndef SCENE_H
#define SCENE_H

#include "Layer2D.h"
#include "ofxCamera.h"
#include "ofxLight.h"

#include <string>
#include <map>
using namespace std;

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        Layer2D* addLayer2D(string id);
        Layer2D* getLayer2D(string id);

        void draw();
        void setBackground(int r, int g, int b);
        ofxCamera* addCamera(string id);
        ofxCamera* activateCamera(string id);

        ofxLight* addLight(string id);
        ofxLight* getLight(string id);
    private:

};

#endif // SCENE_H