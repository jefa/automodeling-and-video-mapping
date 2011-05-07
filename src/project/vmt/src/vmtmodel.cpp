#include "vmtmodel.h"
#include "OscUtil.h"
#include "FileUtil.h"
#include "base64.h"
#include "FadeEffect.h"
#include "TextureEffect.h"
#include "PositionEffect.h"

VmtModel::VmtModel() {
    scene = new Scene();
    oscManager = new OscManager();
    //won't do anything at construct time...
    oscManager->Init(network);

    timeManager = new TimeManager();
}

VmtModel::~VmtModel() {
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

    string effId = timeManager->Update();
    if(!effId.empty()) {
        testEffect(effId);
    }
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

void VmtModel::setBackground(float r, float g, float b){
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

map<string, QuadGroup*> VmtModel::getGroups(){
    return scene->getGroups();
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

Layer2D* VmtModel::getLayer2D(string layId){
    return scene->getActiveCamera()->getLayer2D(layId);
}

ofxLight* VmtModel::getLight(string lightId){
    return scene->getLight(lightId);
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

void VmtModel::addTextureGroupEffect(string effectId, string groupId, string texturePath, textureType type){
    if (scene->getGroup(groupId) == NULL){
        printf("VmtModel::addTextureGroupEffect: group does not exists(%s)\n", groupId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createAddTextureGroupEffectMsg(effectId, groupId, texturePath, type));
    scene->addEffect(effectId, new TextureEffect(effectId, scene->getGroup(groupId), texturePath, type));
}

void VmtModel::addTextureObjectEffect(string effectId, string objId, string facesId, string texturePath, textureType type) {
    if (scene->getObject3D(objId) == NULL){
        printf("VmtModel::addTextureObjectEffect: object does not exists(%s)\n", objId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createAddTextureObjectEffectMsg(effectId, objId, facesId, texturePath, type));
    scene->addEffect(effectId, new TextureEffect(effectId, scene->getObject3D(objId), facesId, texturePath, type));
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

void VmtModel::OrbitActiveCamera(int dx, int dy) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    float angleX = -dx * 0.5f;
    float angleY = dy * 0.5f;

    cam->orbitAround(cam->getEye(), ofxVec3f(0,1,0), angleX);

    ofxVec3f dir = -(cam->getDir());
    ofxVec3f axis2 = dir.getCrossed(ofxVec3f(0,1,0));
    axis2.normalize();

    cam->orbitAround(cam->getEye(), axis2, angleY);
}

void VmtModel::RollActiveCamera(int dx) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    float angleX = -dx * 0.5f;

    ofxVec3f dir = -(cam->getDir());
    ofxVec3f up = cam->getUp();
    up.rotate(angleX, dir);
    cam->up(up);
}

void VmtModel::DollyActiveCamera(int dy) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    float delta = dy * 0.5f;

    ofxVec3f dir = -(cam->getDir());
    dir.normalize();

    ofxVec3f pos = cam->getPosition();
    pos += dir * dy;

    cam->position(pos);
}

void VmtModel::PanActiveCamera(int dx, int dy) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    float moveX = -dx * 0.25f;
    float moveY = dy * 0.25f;

    ofxVec3f dir = -(cam->getDir());
    dir.normalize();
    ofxVec3f up = cam->getUp();
    up.normalize();
    ofxVec3f left = up.crossed(dir);
    ofxVec3f move = left * moveX + up * moveY;

    cam->moveGlobal(move);
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

    showXML.addTag("vmtshow");
    showXML.addAttribute("vmtshow", "name", "showname1", 0);

    showXML.pushTag("vmtshow", 0);

    SerializedNode* sceneNode = scene->Serialize();
    addXMLNode(showXML, sceneNode);

    SerializedNode* timedEventsNode = timeManager->Serialize();
    addXMLNode(showXML, timedEventsNode);

    showXML.popTag();//vmtshow

    showXML.saveFile(filepath);
}

ofxVec2f parseVector2f(string str) {
    std::stringstream sstr(str);
    float x, y;
    sstr >> x >> y;
    return ofxVec2f(x,y);
}

ofxVec3f parseVector3f(string str) {
    std::stringstream sstr(str);
    float x,y,z;
    sstr >> x >> y >> z;
    return ofxVec3f(x,y,z);
}

bool parseBool(string str) {
    return str.compare("true") == 0;
}

void VmtModel::loadShow(string filepath) {
    showXML.loadFile(filepath);

    showXML.pushTag("vmtshow");

        ofxVec3f bgColor = parseVector3f(showXML.getAttribute("scene", "backgroundcolor", "0 0 0", 0));
        this->setBackground(bgColor.x, bgColor.y, bgColor.y);

    showXML.pushTag("scene");

    showXML.pushTag("cameras");
        for(int camI = 0; camI < showXML.getNumTags("camera"); camI++) {
            string camId = showXML.getAttribute("camera", "id", "", camI);
            this->addCamera(camId);
            this->activateCamera(camId);

            showXML.pushTag("camera", camI);

                ofxVec3f camPos = parseVector3f(showXML.getAttribute("view", "pos", "0 0 0", 0));
                this->setCameraPos(camId, camPos.x, camPos.y, camPos.z);

                ofxVec3f camEye = parseVector3f(showXML.getAttribute("view", "eye", "0 0 0", 0));
                this->setCameraEye(camId, camEye.x, camEye.y, camEye.z);

                showXML.pushTag("layers", 0);
                for(int layerI = 0; layerI < showXML.getNumTags("layer"); layerI++) {
                    string layerId = showXML.getAttribute("layer", "id", "", layerI);
                    this->addLayer(camId, layerId);
                    showXML.pushTag("layer", layerI);
                    for(int quadI = 0; quadI < showXML.getNumTags("quad"); quadI++) {
                        string quadId = showXML.getAttribute("quad", "id", "", quadI);
                        bool quadEnabled = parseBool(showXML.getAttribute("quad", "enabled", "true", quadI));
                        ofxVec2f quadP0 = parseVector2f(showXML.getAttribute("quad", "p0", "0 0", quadI));
                        ofxVec2f quadP1 = parseVector2f(showXML.getAttribute("quad", "p1", "0 1", quadI));
                        ofxVec2f quadP2 = parseVector2f(showXML.getAttribute("quad", "p2", "1 1", quadI));
                        ofxVec2f quadP3 = parseVector2f(showXML.getAttribute("quad", "p3", "1 0", quadI));
                        this->addQuad(camId, layerId, quadId);
                        this->enableQuad(camId, layerId, quadId, quadEnabled);
                        this->setQuadPoint(camId, layerId, quadId, 0, quadP0.x, quadP0.y);
                        this->setQuadPoint(camId, layerId, quadId, 1, quadP1.x, quadP1.y);
                        this->setQuadPoint(camId, layerId, quadId, 2, quadP2.x, quadP2.y);
                        this->setQuadPoint(camId, layerId, quadId, 3, quadP3.x, quadP3.y);
                    }
                    showXML.popTag();//layer
                }
                showXML.popTag();//layers
            showXML.popTag();//camera
        }
    showXML.popTag();//cameras

    showXML.pushTag("lights");
    for(int lightI = 0; lightI < showXML.getNumTags("light"); lightI++) {
        string lightId = showXML.getAttribute("light", "id", "", lightI);
        this->addLight(lightId);
    }
    showXML.popTag();//lights

    showXML.pushTag("groups");
    for(int groupI = 0; groupI < showXML.getNumTags("group"); groupI++) {
        string groupId = showXML.getAttribute("group", "id", "", groupI);
        this->addGroup(groupId);
        showXML.pushTag("group", groupI);
        for(int quadI = 0; quadI < showXML.getNumTags("quad"); quadI++) {
            string quadId = showXML.getAttribute("quad", "id", "", quadI);
            //TODO: Agregar el quad al grupo, para esto preciso la camara y layer del quad
            //Es mas sencillo tener un mapa global en la escena con los quads y que no se precise cam y layer.
        }
        showXML.popTag();//group
    }
    showXML.popTag();//groups

    showXML.pushTag("objects3d");
    for(int object3dI = 0; object3dI < showXML.getNumTags("object3d") ; object3dI++) {
        string object3dId = showXML.getAttribute("object3d", "id", "", object3dI);
        string obj3dfilename = showXML.getAttribute("object3d", "filename", "", object3dI);
        ofxVec3f obj3dPos = parseVector3f(showXML.getAttribute("object3d", "pos", "", object3dI));
        ofxVec3f obj3dScale = parseVector3f(showXML.getAttribute("object3d", "scale", "", object3dI));
        this->addObject3D(object3dId, obj3dfilename);
    }
    showXML.popTag();//objects3d;

    showXML.pushTag("effects");
    for(int effectI = 0; effectI < showXML.getNumTags("effect"); effectI++) {
        string effectId = showXML.getAttribute("effect", "id", "", effectI);
        //FALTA parsear el tipo de efecto que se está guardando mal y el resto de los params.
    }
    showXML.popTag();//effects

    showXML.popTag();//scene
    showXML.popTag();//vmtshow
}

void getNodeFromXML(ofxXmlSettings &xml, SerializedNode *node) {

}

map<string, ofxCamera*> VmtModel::getCameras() {
    return this->scene->getCameras();
}

map<string, Object3D*> VmtModel::getObjects3D() {
    return this->scene->getObjects3D();
}

map<string, Effect*> VmtModel::getEffects() {
    return this->scene->getEffects();
}

void VmtModel::scheduleEvent(float time, string effectId) {
    timeManager->ScheduleEvent(time, effectId);
}

void VmtModel::startTimeManager(TIMER_MODE mode) {
    timeManager->Start(mode);
}
