#include "Scene.h"
#include "ofMain.h"

map<string, ofxCamera*>::iterator camerasIt;
map<string, Mesh3D*>::iterator meshesIt;

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

ofxLight* Scene::addLight(string id) {
    ofxLight* light = new ofxLight();
    lights.insert(pair<string, ofxLight*>(id, light));
    return light;
}

ofxLight* Scene::getLight(string id) {
    return lights[id];
}

Mesh3D* Scene::addMesh3D(string id, string path) {
    Mesh3D *mesh = new Mesh3D(path);
    meshes.insert(pair<string, Mesh3D*>(id, mesh));
}

void Scene::draw() {

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

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

    for(meshesIt = meshes.begin(); meshesIt != meshes.end(); meshesIt++) {
        meshesIt->second->draw();
    }

    ofxLightsOff(); //turn lights off to draw text

    activeCamera->remove();

    activeCamera->drawLayers();
}

void Scene::setBackground(int r, int g, int b) {
    ofBackground(r,g,b);
}
