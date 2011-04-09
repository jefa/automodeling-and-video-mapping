#include "Scene.h"
#include "ofMain.h"

map<string, ofxCamera*>::iterator camerasIt;
map<string, Object3D*>::iterator objects3DIt;

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
    return activeCamera;
}

ofxCamera* Scene::getActiveCamera() {
    return activeCamera;
}

map<string, ofxCamera*> Scene::getCameras() {
    return this->cameras;
}

ofxLight* Scene::addLight(string id) {
    ofxLight* light = new ofxLight();
    lights.insert(pair<string, ofxLight*>(id, light));
    return light;
}

ofxLight* Scene::getLight(string id) {
    return lights[id];
}

Object3D* Scene::addObject3D(string id, string path) {
    Object3D *obj3D = new Object3D(path);
    objects3D.insert(pair<string, Object3D*>(id, obj3D));
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
            //camerasIt->second->drawCamera(true);
            camerasIt->second->drawCamera2();
    }

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    for(objects3DIt = objects3D.begin(); objects3DIt != objects3D.end(); objects3DIt++) {
        objects3DIt->second->draw();
    }

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    ofxLightsOff(); //turn lights off to draw text

    activeCamera->remove();

    //Draw the 2d layers after removing the camera.
    activeCamera->drawLayers();
}

void Scene::setBackground(int r, int g, int b) {
    ofBackground(r,g,b);
}
