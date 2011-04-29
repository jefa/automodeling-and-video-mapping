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
    scene->addEffect(effectId, new PositionEffect(scene->getObject3D(objId), posIni, posFin, delay));
}

void VmtModel::addFadeEffect(string effectId, string groupId, ofxVec4f colorIni, ofxVec4f colorFin, float delay){
    if (scene->getGroup(groupId) == NULL){
        printf("VmtModel::addFadeEffect: group does not exists(%s)\n", groupId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createAddFadeEffectMsg(effectId, groupId, colorIni, colorFin, delay));
    scene->addEffect(effectId, new FadeEffect(scene->getGroup(groupId), colorIni, colorFin, delay));
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

void VmtModel::saveShow(string filepath) {
    showXML.clear();
    std::stringstream sstr;

    showXML.addTag("vmtshow");
    showXML.addAttribute("vmtshow", "name", "showname1", 0);

    showXML.pushTag("vmtshow", 0);

    showXML.addTag("cameras");
    showXML.pushTag("cameras",0);

    map<string, ofxCamera*> camerasMap = scene->getCameras();
    map<string, ofxCamera*>::iterator camerasIt;
    for(camerasIt = camerasMap.begin(); camerasIt != camerasMap.end(); camerasIt++) {

        int camI = showXML.addTag("camera");
        showXML.addAttribute("camera", "id", camerasIt->first, camI);
        showXML.addAttribute("camera", "type", camerasIt->second->isProjector() ? "projector" : "camera", camI);

        showXML.pushTag("camera", camI);

        showXML.addTag("view");

        ofxVec3f pos = camerasIt->second->getPosition();
        sstr.str("");
        sstr << pos.x << " " << pos.y << " " << pos.z;
        showXML.addAttribute("view", "pos", sstr.str(), 0);

        ofxVec3f eye = camerasIt->second->getEye();

        sstr.str("");
        sstr << eye.x << " " << eye.y << " " << eye.z;
        showXML.addAttribute("view", "eye", sstr.str(), 0);

        showXML.addAttribute("view", "up", "0", 0);

        showXML.addTag("projection");
        //TODO: Agregar valores de proyeccion.
        //<projection fov="45" aspect="1.33" resx="1024" resy="768"/>

        showXML.addTag("layers");
        showXML.pushTag("layers", 0);

        map<string, Layer2D*> layers2D = camerasIt->second->getLayers2D();
        map<string, Layer2D*>::iterator layersIt;
        for(layersIt = layers2D.begin(); layersIt != layers2D.end(); layersIt++) {
            int layerI = showXML.addTag("layer");
            showXML.addAttribute("layer", "id", layersIt->first, layerI);
            showXML.pushTag("layer");

            map<string, Quad2D*> quads2D = layersIt->second->getQuads2D();
            map<string, Quad2D*>::iterator quadsIter;
            for (quadsIter=quads2D.begin(); quadsIter != quads2D.end(); quadsIter++) {
                int quadI = showXML.addTag("quad");
                showXML.addAttribute("quad", "id", quadsIter->first, quadI);
                showXML.addAttribute("quad", "enabled", quadsIter->second->isEnabled() ? "true" : "false", quadI);

                ofxVec2f p0 = quadsIter->second->getPoint(0);
                ofxVec2f p1 = quadsIter->second->getPoint(1);
                ofxVec2f p2 = quadsIter->second->getPoint(2);
                ofxVec2f p3 = quadsIter->second->getPoint(3);

                sstr.str("");
                sstr << p0.x << " " << p0.y;
                showXML.addAttribute("quad", "p0", sstr.str() , quadI);
                sstr.str("");
                sstr << p1.x << " " << p1.y;
                showXML.addAttribute("quad", "p1", sstr.str() , quadI);
                sstr.str("");
                sstr << p2.x << " " << p2.y;
                showXML.addAttribute("quad", "p2", sstr.str() , quadI);
                sstr.str("");
                sstr << p3.x << " " << p3.y;
                showXML.addAttribute("quad", "p3", sstr.str() , quadI);
            }

            showXML.popTag();
        }

        showXML.popTag();//layers
        showXML.popTag();//camera
    }
    showXML.popTag();//cameras

    showXML.addTag("objects3d");
    showXML.pushTag("objects3d", 0);

    map<string, Object3D*> objects3D = scene->getObjects3D();
    map<string, Object3D*>::iterator objects3DIt;
    for(objects3DIt = objects3D.begin(); objects3DIt != objects3D.end(); objects3DIt++) {
        int object3DI = showXML.addTag("object3d");
        showXML.addAttribute("object3d", "id", objects3DIt->first, object3DI);

        showXML.addAttribute("object3d", "filename", objects3DIt->second->getPath(), object3DI);

        ofxVec3f pos = objects3DIt->second->getPosition();
        ofxVec3f scale = objects3DIt->second->getScale();

        sstr.str("");
        sstr << pos.x << " " << pos.y << " " << pos.z;
        showXML.addAttribute("object3d", "pos", sstr.str(), object3DI);

        sstr.str("");
        sstr << scale.x << " " << scale.y << " " << scale.z;
        showXML.addAttribute("object3d", "scale", sstr.str(), object3DI);

        //TODO: Falta la rotacion, es mas complicado que 3 angulos
        //<object3d id="squirrel" filename="data/squirrel.3ds" pos="1.22 2.33 3.44" ang="20 10 30" scale="10 20 30"/>
    }
    showXML.popTag(); //objects3d

    showXML.popTag();//vmtshow

    showXML.saveFile(filepath);
}

map<string, ofxCamera*> VmtModel::getCameras() {
    return this->scene->getCameras();
}

map<string, Object3D*> VmtModel::getObjects3D() {
    return this->scene->getObjects3D();
}
