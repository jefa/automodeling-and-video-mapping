#include "vmtmodel.h"
#include "OscUtil.h"
#include "FileUtil.h"
#include "base64.h"
#include "FadeEffect.h"
#include "PositionEffect.h"

VmtModel::VmtModel()
{
    scene = new Scene();
    oscManager = new OscManager();
    //won't do anything at construct time...
    oscManager->Init(network);
}

VmtModel::~VmtModel()
{
    delete scene;
    delete oscManager;
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

void VmtModel::addNetNode(string nodeId, string address, int port, bool isActive, string camId){
    Node nd;
    nd.address = address;
    nd.port = port;
    nd.isActive = isActive;
    nd.cameraId = camId;

    network.insert(pair<string, Node>(nodeId, nd));

    //re-init OscManager
    this->oscManager->Init(this->network);
}

string VmtModel::getNodeForCamera(string camId){
    map<string, Node>::iterator iter = network.begin();
    while (iter != network.end()) {
        //printf("VmtModel.getNodeForCamera:: nodeId=%s, nodeCameraId=%s, reqCamId=%s\n", iter->first.c_str(), iter->second.cameraId.c_str(), camId.c_str());
        if (iter->second.cameraId == camId){
            return iter->first;
        }
        iter++;
    }
    //printf("VmtModel.getNodeForCamera:: Can't find node for camera %s\n", camId.c_str());
    return "";
}

void VmtModel::setBackground(int r, int g, int b){
    oscManager->SendMessageAll(OscUtil::createSetBackgroundMsg(r, g, b));
    scene->setBackground(r,g,b);
}

void VmtModel::addCamera(string id){
    oscManager->SendMessage(OscUtil::createAddCameraMsg(id), getNodeForCamera(id));
    scene->addCamera(id);
}

void VmtModel::setCameraPos(string camId, float x, float y, float z){
    oscManager->SendMessage(OscUtil::createSetCameraPosMsg(camId, ofxVec3f(x, y, z)), getNodeForCamera(camId));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        camera->position(x, y, z);
    }
    else {
        ofLog(OF_LOG_ERROR, "VmtModel::setCameraPos camera %s is NULL", camId.c_str());
    }
}

void VmtModel::setCameraEye(string camId, float x, float y, float z){
    oscManager->SendMessage(OscUtil::createSetCameraEyeMsg(camId, ofxVec3f(x, y, z)), getNodeForCamera(camId));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        camera->eye(x, y, z);
    }
    else {
        ofLog(OF_LOG_ERROR, "VmtModel::setCameraEye camera %s is NULL", camId.c_str());
    }
}

void VmtModel::activateCamera(string camId){
    oscManager->SendMessage(OscUtil::createActivateCameraMsg(camId), getNodeForCamera(camId));
    scene->activateCamera(camId);
}

ofxCamera* VmtModel::getActiveCamera(){
    return scene->getActiveCamera();
}

void VmtModel::addGroup(string groupId){
    oscManager->SendMessageAll(OscUtil::createAddGroupMsg(groupId));
    scene->addGroup(groupId);
}

QuadGroup* VmtModel::getGroup(string groupId){
    return scene->getGroup(groupId);
}

void VmtModel::addLayer(string camId, string layerId){
    oscManager->SendMessage(OscUtil::createAddLayerMsg(camId, layerId), getNodeForCamera(camId));
    if (scene->getCamera(camId) != NULL)
        scene->getCamera(camId)->addLayer2D(layerId);
}

void VmtModel::addQuad(string camId, string layerId, string quadId){
    oscManager->SendMessage(OscUtil::createAddQuadMsg(camId, layerId, quadId), getNodeForCamera(camId));
    if (scene->getCamera(camId) != NULL) {
        ofxCamera *camera = scene->getCamera(camId);
        if (camera->getLayer2D(layerId) != NULL)
            camera->getLayer2D(layerId)->addQuad2D(quadId);
    }
}

void VmtModel::addQuadToGroup(string groupId, string camId, string layerId, string quadId){
    oscManager->SendMessage(OscUtil::createAddQuadToGroupMsg(groupId, camId, layerId, quadId), getNodeForCamera(camId));
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
    oscManager->SendMessage(OscUtil::createEnableQuadMsg(camId, layerId, quadId, enabled), getNodeForCamera(camId));
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
    oscManager->SendMessage(OscUtil::createSetQuadPointMsg(camId, layerId, quadId, point, coordX, coordY), getNodeForCamera(camId));
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

/*    FILE * pFile;
    long lSize;
    size_t result;

    pFile = fopen ( path.c_str() , "rb" );
    if (pFile==NULL) {
        fputs ("File error",stderr);
        return;
    }

    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    char* buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {
        fputs ("Memory error",stderr);
        return ;
    }

    result = fread (buffer, 1, lSize, pFile);
    if (result != lSize) {
        fputs ("Reading error",stderr);
        return ;
    }

    fclose (pFile);

    string base64strEncoded = base64_encode((unsigned char*)buffer , lSize);
*/
    oscManager->SendMessageAll(OscUtil::createAddObject3dMsg(objId, path /*base64strEncoded*/));
    scene->addObject3D(objId, path);
}

Object3D* VmtModel::getObject3D(string objId){
    return scene->getObject3D(objId);
}

void VmtModel::addPositionEffect(string effectId, string objId, ofxVec3f posIni, ofxVec3f posFin, float delay){
    if (scene->getObject3D(objId) == NULL){
        printf("VmtModel::addPositionEffect: object does not exists(%s)\n", objId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createAddPositionEffectMsg(effectId, objId, posIni, posFin, delay));
    scene->addEffect(effectId, new PositionEffect(effectId, scene->getObject3D(objId), posIni, posFin, delay));
}

void VmtModel::addFadeEffect(string effectId, string groupId, ofxVec4f colorIni, ofxVec4f colorFin, float delay){
    if (scene->getGroup(groupId) == NULL){
        printf("VmtModel::addFadeEffect: group does not exists(%s)\n", groupId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createAddFadeEffectMsg(effectId, groupId, colorIni, colorFin, delay));
    scene->addEffect(effectId, new FadeEffect(effectId, scene->getGroup(groupId), colorIni, colorFin, delay));
}

void VmtModel::addTextureEffect(string effectId){
    throw exception();
}

void VmtModel::testEffect(string id){
    oscManager->SendMessageAll(OscUtil::createTestEffectMsg(id));
    this->scene->testEffect(id);
}

void VmtModel::addLight(string lightId){
    oscManager->SendMessageAll(OscUtil::createAddLightMsg(lightId));
    scene->addLight(lightId);
}

void VmtModel::setLightSpecular(string lightId, float r, float g, float b){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createLightSpecularMsg(lightId, r, g, b));
    scene->getLight(lightId)->specular(r, g, b);
}

void VmtModel::setLightDirectional(string lightId, float r, float g, float b,
                                   float nx, float ny, float nz){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createLightDirectionalMsg(lightId, r, g, b, nx, ny, nz));
    scene->getLight(lightId)->directionalLight(r, g, b, nx, ny, nz);
}

void VmtModel::setLightSpot(string lightId, float r, float g, float b,
                                   float x, float y, float z,
                                   float nx, float ny, float nz,
                                   float angle, float concentration){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createLightSpotMsg(lightId, r, g, b, x, y, z, nx, ny, nz, angle, concentration));
    scene->getLight(lightId)->spotLight(r, g, b, x, y, z, nx, ny, nz, angle, concentration);
}

void VmtModel::setLightPoint(string lightId, float r, float g, float b,
                                   float x, float y, float z){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createLightPointMsg(lightId, r, g, b, x, y, z));
    scene->getLight(lightId)->pointLight(r, g, b, x, y, z);
}

void addXMLNode(ofxXmlSettings &xml, SerializedNode* node) {
    int tagI = xml.addTag(node->getTagId());

    vector<pair<string, string> > attributes = node->getAttributes();
    vector<pair<string, string> >::iterator attributesIt;
    for(attributesIt = attributes.begin(); attributesIt != attributes.end(); attributesIt++) {
        xml.addAttribute(node->getTagId(), attributesIt->first, attributesIt->second, tagI);
    }

    xml.pushTag(node->getTagId(), tagI);

    vector<SerializedNode*> childNodes = node->getChildNodes();
    vector<SerializedNode*>::iterator childNodesIt;
    for(childNodesIt = childNodes.begin(); childNodesIt != childNodes.end(); childNodesIt++) {
        addXMLNode(xml, *childNodesIt);
    }
    xml.popTag();
}

void VmtModel::saveShow(string filepath) {
    showXML.clear();
    std::stringstream sstr;

    showXML.addTag("vmtshow");
    showXML.addAttribute("vmtshow", "name", "showname1", 0);

    showXML.pushTag("vmtshow", 0);

    SerializedNode* node = scene->Serialize();
    addXMLNode(showXML, node);

    showXML.popTag();//vmtshow

    showXML.saveFile(filepath);
}

map<string, ofxCamera*> VmtModel::getCameras() {
    return this->scene->getCameras();
}

map<string, Object3D*> VmtModel::getObjects3D() {
    return this->scene->getObjects3D();
}
