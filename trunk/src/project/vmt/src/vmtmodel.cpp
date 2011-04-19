#include "vmtmodel.h"

#include "OscUtil.h"

VmtModel::VmtModel()
{
    scene = new Scene();
    oscManager = new OscManager();

    Node nd;
    nd.address = "localhost";
    nd.port = 54321;
    nd.isActive = true;

    map<string, Node> net;
    net.insert(pair<string, Node>("nodo1", nd));

    oscManager->Init(net);

}

VmtModel::~VmtModel()
{
    delete scene;
}

Scene* VmtModel::getScene(){
    return this->scene;
}

void VmtModel::draw(){
    this->scene->draw();
}

void VmtModel::update(){
    this->scene->update();
}

void VmtModel::setBackground(int r, int g, int b){
    scene->setBackground(r,g,b);
}

void VmtModel::addCamera(string id){
    oscManager->SendMessage(OscUtil::createAddCameraMsg(id));
    scene->addCamera(id);
}

void VmtModel::setCameraPos(string camId, float x, float y, float z){
    oscManager->SendMessage(OscUtil::createSetCameraPosMsg(camId, ofxVec3f(x, y, z)));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL)
        camera->position(x, y, z);
}

void VmtModel::setCameraEye(string camId, float x, float y, float z){
    oscManager->SendMessage(OscUtil::createSetCameraEyeMsg(camId, ofxVec3f(x, y, z)));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL)
        camera->eye(x, y, z);
}

void VmtModel::activateCamera(string camId){
    oscManager->SendMessage(OscUtil::createActivateCameraMsg(camId));
    scene->activateCamera(camId);
}

ofxCamera* VmtModel::getActiveCamera(){
    return scene->getActiveCamera();
}

void VmtModel::addGroup(string groupId){
    scene->addGroup(groupId);
}

QuadGroup* VmtModel::getGroup(string groupId){
    return scene->getGroup(groupId);
}

void VmtModel::addLayer(string camId, string layerId){
    oscManager->SendMessage(OscUtil::createAddLayerMsg(camId, layerId));
    if (scene->getCamera(camId) != NULL)
        scene->getCamera(camId)->addLayer2D(layerId);
}

void VmtModel::addQuad(string camId, string layerId, string quadId){
    oscManager->SendMessage(OscUtil::createAddQuadMsg(camId, layerId, quadId));
    if (scene->getCamera(camId) != NULL) {
        ofxCamera *camera = scene->getCamera(camId);
        if (camera->getLayer2D(layerId) != NULL)
            camera->getLayer2D(layerId)->addQuad2D(quadId);
    }
}

void VmtModel::addQuadToGroup(string groupId, string camId, string layerId, string quadId){
    QuadGroup *group = scene->getGroup(groupId);
    if (group != NULL) {
        ofxCamera *camera = scene->getCamera(camId);
        if (camera != NULL) {
            Layer2D *layer = camera->getLayer2D(layerId);
            if (layer != NULL){
                Quad2D *quad = layer->getQuad2D(quadId);
                if (quad != NULL)
                    group->addQuad2D(quad);
            }
        }
    }
}

void VmtModel::enableQuad(string camId, string layerId, string quadId, bool enabled){
    oscManager->SendMessage(OscUtil::createEnableQuadMsg(camId, layerId, quadId, enabled));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        Layer2D *layer = camera->getLayer2D(layerId);
        if (layer != NULL){
            Quad2D *quad = layer->getQuad2D(quadId);
            if (quad != NULL)
                quad->setEnabled(enabled);
        }
    }
}

void VmtModel::setQuadPoint(string camId, string layerId, string quadId,
            int point, float coordX, float coordY){
    oscManager->SendMessage(OscUtil::createSetQuadPointMsg(camId, layerId, quadId, point, coordX, coordY));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        Layer2D *layer = camera->getLayer2D(layerId);
        if (layer != NULL){
            Quad2D *quad = layer->getQuad2D(quadId);
            if (quad != NULL)
                quad->setPoint(point, coordX, coordY);
        }
    }
}

void VmtModel::addObject3D(string objId, string path){
    scene->addObject3D(objId, path);
}

Object3D* VmtModel::getObject3D(string objId){
    return scene->getObject3D(objId);
}

void VmtModel::addEffect(string effectId, Effect *ef){
    scene->addEffect(effectId, ef);
}

void VmtModel::testEffect(string id){
    this->scene->testEffect(id);
}

void VmtModel::addLight(string lightId){
    scene->addLight(lightId);
}

void VmtModel::setLightSpecular(string lightId, float r, float g, float b){
    if (scene->getLight(lightId) != NULL)
        scene->getLight(lightId)->specular(r, g, b);
}

void VmtModel::setLightDirectional(string lightId, float r, float g, float b,
                                   float nx, float ny, float nz){
    if (scene->getLight(lightId) != NULL)
        scene->getLight(lightId)->directionalLight(r, g, b, nx, ny, nz);
}

void VmtModel::setLightSpot(string lightId, float r, float g, float b,
                                   float x, float y, float z,
                                   float nx, float ny, float nz,
                                   float angle, float concentration){
    if (scene->getLight(lightId) != NULL)
        scene->getLight(lightId)->spotLight(r, g, b, x, y, z, nx, ny, nz, angle, concentration);
}

void VmtModel::setLightPoint(string lightId, float r, float g, float b,
                                   float x, float y, float z){
    if (scene->getLight(lightId) != NULL)
        scene->getLight(lightId)->pointLight(r, g, b, x, y, z);
}
