#include "Scene.h"
#include "ofMain.h"
#include "AnimationManager.h"

map<string, ofxCamera*>::iterator camerasIt;
map<string, Object3D*>::iterator objects3DIt;

Scene::Scene() {
    activeCamera = NULL;
}

Scene::~Scene() {
    activeCamera = NULL;
}

ofxCamera* Scene::addCamera(string id) {
    ofxCamera* camera = new ofxCamera();
    camera->setId(id);
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

QuadGroup* Scene::addGroup(string id) {
    QuadGroup *group = new QuadGroup(id);
    quadGroups.insert(pair<string, QuadGroup*>(id, group));
    return group;
}

QuadGroup* Scene::getGroup(string id) {
    return quadGroups[id];
}

map<string, QuadGroup*> Scene::getGroups() {
    return quadGroups;
}

Object3D* Scene::addObject3D(string id, string path) {
    Object3D *obj3D = new Object3D(id, path);
    objects3D.insert(pair<string, Object3D*>(id, obj3D));
    return obj3D;
}

Object3D* Scene::getObject3D(string id) {
    return objects3D[id];
}

map<string, Object3D*> Scene::getObjects3D() {
    return objects3D;
}

Object3D* Scene::activateObject(string id) {
    activeObject = objects3D[id];
    return activeObject;
}

Object3D* Scene::getActiveObject() {
    return activeObject;
}

void Scene::deActivateObject() {
    activeObject = NULL;
}

Effect* Scene::addEffect(string id, Effect* effect) {
    effects.insert(pair<string, Effect*>(id, effect));
    return effect;
}

void Scene::testEffect(string id) {
    effects[id]->test();
}

map<string, Effect*> Scene::getEffects() {
    return effects;
}

void Scene::update() {
    AnimationManager::Update();
    TextureManager::Update();
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
            camerasIt->second->drawCamera();
    }

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    for(objects3DIt = objects3D.begin(); objects3DIt != objects3D.end(); objects3DIt++) {
        objects3DIt->second->draw();
    }

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    ofxLightsOff(); //turn lights off to draw text

    activeCamera->remove();

    //Draw the 2d layers after removing the camera.

    glDisable(GL_DEPTH_TEST);
    activeCamera->drawLayers();
    glEnable(GL_DEPTH_TEST);
}

void Scene::setBackground(int r, int g, int b) {
    ofBackground(r,g,b);
}

SerializedNode* Scene::Serialize() {
    SerializedNode *node = new SerializedNode("scene");

    SerializedNode *camerasNode = new SerializedNode("cameras");
    for(camerasIt = cameras.begin(); camerasIt != cameras.end(); camerasIt++) {
        camerasNode->addChildNode(camerasIt->second->Serialize());
    }
    node->addChildNode(camerasNode);

    SerializedNode *groupsNode = new SerializedNode("groups");
    map<string, QuadGroup*>::iterator groupsIt;
    for(groupsIt = quadGroups.begin(); groupsIt != quadGroups.end(); groupsIt++) {
        groupsNode->addChildNode(groupsIt->second->Serialize());
    }
    node->addChildNode(groupsNode);

    SerializedNode *objects3dNode = new SerializedNode("objects3d");
    for(objects3DIt = objects3D.begin(); objects3DIt != objects3D.end(); objects3DIt++) {
        objects3dNode->addChildNode(objects3DIt->second->Serialize());
    }
    node->addChildNode(objects3dNode);

    SerializedNode *effectsNode = new SerializedNode("effects");
    map<string, Effect*>::iterator effectsIt;
    for(effectsIt = effects.begin(); effectsIt != effects.end(); effectsIt++) {
        effectsNode->addChildNode(effectsIt->second->Serialize());
    }
    node->addChildNode(effectsNode);

    return node;
}
