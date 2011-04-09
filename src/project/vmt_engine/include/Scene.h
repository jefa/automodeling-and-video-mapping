#ifndef SCENE_H
#define SCENE_H

#include "ofxCamera.h"
#include "ofxLight.h"
#include "Object3D.h"

#include <string>
#include <map>
using namespace std;

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        void draw();
        void setBackground(int r, int g, int b);
        ofxCamera* addCamera(string id);
        ofxCamera* getCamera(string id);
        ofxCamera* activateCamera(string id);
        ofxCamera* getActiveCamera();
        map<string, ofxCamera*> getCameras();

        ofxLight* addLight(string id);
        ofxLight* getLight(string id);

        Object3D* addObject3D(string id, string path);

    private:
        map<string, ofxCamera*> cameras;
        ofxCamera* activeCamera;
        map<string, ofxLight*> lights;
        map<string, Object3D*> objects3D;
};

#endif // SCENE_H
