#include "Scene.h"
#include "ofMain.h"

map<string, Layer2D*>::iterator layersIt;
map<string, ofxCamera*>::iterator camerasIt;

Scene::Scene() {
    activeCamera = NULL;
}

Scene::~Scene() {
    //dtor
}

ofxCamera* Scene::addCamera(string id) {
    ofxCamera* camera = new ofxCamera();
    cameras.insert(pair<string, ofxCamera*>(id, camera));
    return camera;
}

ofxCamera* Scene::getCamera(string id) {
    return cameras[id];
}

ofxCamera* Scene::activateCamera(string id) {
    activeCamera = cameras[id];
    return getActiveCamera();
}

ofxCamera* Scene::getActiveCamera() {
    return activeCamera;
}

ofxLight* Scene::addLight(string id) {
    ofxLight* light = new ofxLight();
    lights.insert(pair<string, ofxLight*>(id, light));
    return light;
}

ofxLight* Scene::getLight(string id) {
    return lights[id];
}

void Scene::draw() {

    if(activeCamera == NULL) {
        ofLog(OF_LOG_ERROR, "There is no active camera.");
        return;
    }
    activeCamera->place();

	ofxLightsOn(); //turn lights on
	ofSetColor(255, 255, 255);

    map<string, ofxCamera*> camerasMap = this->cameras;
    for(camerasIt = camerasMap.begin(); camerasIt != camerasMap.end(); camerasIt++) {
        if (camerasIt->second != activeCamera)
            camerasIt->second->drawCamera(true);
    }

    //draw3D

    ofxLightsOff(); //turn lights off to draw text

    activeCamera->remove();

    for(layersIt = activeCamera->getLayers2D().begin();
        layersIt != activeCamera->getLayers2D().end(); layersIt++) {
            layersIt->second->draw();
    }

}

void Scene::setBackground(int r, int g, int b) {
    ofBackground(r,g,b);
}
