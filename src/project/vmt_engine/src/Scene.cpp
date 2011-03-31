#include "Scene.h"
#include "ofMain.h"

map<string, Layer2D*>::iterator layersIt;

Scene::Scene() {
    //ctor
}

Scene::~Scene() {
    //dtor
}

ofxCamera* Scene::addCamera(string id) {
    ofxCamera* camera = new ofxCamera();
    cameras.insert(pair<string, ofxCamera*>(id, camera));
    return camera;
}

ofxCamera* Scene::activateCamera(string id) {
    activeCamera = cameras[id];
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

Layer2D* Scene::addLayer2D(string id) {
    Layer2D* layer = new Layer2D();
    layers2D.insert(pair<string, Layer2D*>(id, layer));
    return layer;
}

Layer2D* Scene::getLayer2D(string id) {
    return layers2D[id];
}

map<string, Layer2D*> Scene::getLayers2D() {
    return layers2D;
}

void Scene::draw() {

    activeCamera->place();

	ofxLightsOn(); //turn lights on
	ofSetColor(255, 255, 255);

    //glutSolidTeapot(100);

    ofxLightsOff(); //turn lights off to draw text
    activeCamera->remove();

    //Las layers2D se dibujan sin luces y sin camara.
    for(layersIt = layers2D.begin(); layersIt != layers2D.end(); layersIt++) {
        layersIt->second->draw();
    }
}

void Scene::setBackground(int r, int g, int b) {
    ofBackground(r,g,b);
}
