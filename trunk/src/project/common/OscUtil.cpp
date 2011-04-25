#include "OscUtil.h"
#include "FileUtil.h"
#include "base64.h"

#include "FadeEffect.h"
#include "PositionEffect.h"
#include "TextureEffect.h"

OscUtil::OscUtil()
{
    //ctor
}

OscUtil::~OscUtil()
{
    //dtor
}

ofxOscMessage OscUtil::createSetBackgroundMsg(int r, int g, int b){
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/scene/setbackground");
    oscMessage.addIntArg(r);
    oscMessage.addIntArg(g);
    oscMessage.addIntArg(b);
    return oscMessage;
}

void OscUtil::processSetBackgroundMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    int r = msg.getArgAsInt32(0);
    int g = msg.getArgAsInt32(1);
    int b = msg.getArgAsInt32(2);
    sceneHandler->setBackground(r,g,b);
}

ofxOscMessage OscUtil::createAddCameraMsg(string id)
{
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/camera/add");
    oscMessage.addStringArg(id);
    return oscMessage;
}

void OscUtil::processAddCameraMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string id = msg.getArgAsString(0);
    sceneHandler->addCamera(id);
}

ofxOscMessage OscUtil::createSetCameraPosMsg(string id, ofxVec3f position)
{
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/camera/setpos");
    oscMessage.addStringArg(id);
    oscMessage.addFloatArg(position[0]);
    oscMessage.addFloatArg(position[1]);
    oscMessage.addFloatArg(position[2]);
    return oscMessage;
}

void OscUtil::processSetCameraPosMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string id = msg.getArgAsString(0);
    float x = msg.getArgAsFloat(1);
    float y = msg.getArgAsFloat(2);
    float z = msg.getArgAsFloat(3);
    sceneHandler->setCameraPos(id, x, y, z);
}

ofxOscMessage OscUtil::createSetCameraEyeMsg(string id, ofxVec3f eye)
{
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/camera/seteye");
    oscMessage.addStringArg(id);
    oscMessage.addFloatArg(eye[0]);
    oscMessage.addFloatArg(eye[1]);
    oscMessage.addFloatArg(eye[2]);
    return oscMessage;
}

void OscUtil::processSetCameraEyeMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string id = msg.getArgAsString(0);
    float x = msg.getArgAsFloat(1);
    float y = msg.getArgAsFloat(2);
    float z = msg.getArgAsFloat(3);
    sceneHandler->setCameraEye(id, x, y, z);
}

ofxOscMessage OscUtil::createActivateCameraMsg(string id){
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/camera/activate");
    oscMessage.addStringArg(id);
    return oscMessage;
}

void OscUtil::processActivateCameraMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string camId = msg.getArgAsString(0);
    sceneHandler->activateCamera(camId);
}

ofxOscMessage OscUtil::createAddQuadMsg(string camId, string layerId, string quadId) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/quad/add");
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    return oscMessage;
}

void OscUtil::processAddQuadMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    string camId = msg.getArgAsString(0);
    string layerId = msg.getArgAsString(1);
    string quadId = msg.getArgAsString(2);
    sceneHandler->addQuad(camId, layerId, quadId);
}

ofxOscMessage OscUtil::createSetQuadPointMsg(string camId, string layerId, string quadId,
                                           int point, float coordX, float coordY){
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/quad/setpoint");
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    oscMessage.addIntArg(point);
    oscMessage.addFloatArg(coordX);
    oscMessage.addFloatArg(coordY);
    return oscMessage;
}

void OscUtil::processSetQuadPointMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string camId = msg.getArgAsString(0);
    string layerId = msg.getArgAsString(1);
    string quadId = msg.getArgAsString(2);
    int point = msg.getArgAsInt32(3);
    float coordX = msg.getArgAsFloat(4);
    float coordY = msg.getArgAsFloat(5);
    sceneHandler->setQuadPoint(camId, layerId, quadId, point, coordX, coordY);
}

ofxOscMessage OscUtil::createEnableQuadMsg(string camId, string layerId, string quadId, bool enabled){
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/quad/enable");
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    oscMessage.addIntArg(enabled);
    return oscMessage;
}

void OscUtil::processEnableQuadMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string camId = msg.getArgAsString(0);
    string layerId = msg.getArgAsString(1);
    string quadId = msg.getArgAsString(2);
    bool enabled = msg.getArgAsInt32(3);
    sceneHandler->enableQuad(camId, layerId, quadId, enabled);
}

ofxOscMessage OscUtil::createAddLayerMsg(string camId, string layerId) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/layer/add");
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    return oscMessage;
}

void OscUtil::processAddLayerMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    string camId = msg.getArgAsString(0);
    string layerId = msg.getArgAsString(1);
    sceneHandler->addLayer(camId, layerId);
}

ofxOscMessage OscUtil::createAddGroupMsg(string groupId){
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/group/add");
    oscMessage.addStringArg(groupId);
    return oscMessage;
}

void OscUtil::processAddGroupMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string groupId = msg.getArgAsString(0);
    sceneHandler->addGroup(groupId);
}

ofxOscMessage OscUtil::createAddQuadToGroupMsg(string groupId, string camId, string layerId, string quadId){
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/group/addquad");
    oscMessage.addStringArg(groupId);
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    return oscMessage;
}

void OscUtil::processAddQuadToGroupMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string groupId = msg.getArgAsString(0);
    string camId = msg.getArgAsString(1);
    string layerId = msg.getArgAsString(2);
    string quadId = msg.getArgAsString(3);
    sceneHandler->addQuadToGroup(groupId, camId, layerId, quadId);
}

ofxOscMessage OscUtil::createAddObject3dMsg(string objId, string base64data){
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/object/add");
    oscMessage.addStringArg(objId);

    cout << "\tbase64data.size==== " << base64data.size() << endl;

    int chunks = base64data.size() / 2000;
    int rest = base64data.size() % 2000;
    oscMessage.addIntArg(chunks);
    for (int i=0; i<(chunks-1); i++){
        cout << "\tchunk: " << i << " de " << chunks << endl;
        cout << "\tpos: " << i*2000 << endl;
        //if ( i = (chunks-1))
            //oscMessage.addStringArg(base64data.substr(i * 2000, rest));
        //else
            oscMessage.addStringArg(base64data.substr(i * 2000, 2000));
    }
    oscMessage.addStringArg(base64data.substr((chunks-1) * 2000, rest));

    /*try {
        oscMessage.addStringArg(base64data.substr(0,3000));
    } catch (exception& e)
    {
        cout << "\tEXCEPCIONNNNN!!!!! " << e.what() << endl;
    }*/
    return oscMessage;
}

void OscUtil::processAddObject3dMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string objId = msg.getArgAsString(0);
    int chunks = msg.getArgAsInt32(1);
    //string base64data = msg.getArgAsString(2);
    string base64data;
    for (int i=0; i<chunks; i++){
        base64data += msg.getArgAsString(i+2);
    }
    printf("\tBASE64.DATA=%s\n", base64data.c_str());

    string path = "data/transferred/" + objId + ".3ds";

    string base64strDecoded = base64_decode(base64data);

    bool saved = FileUtil::writeBinaryFile(path, base64strDecoded);

    sceneHandler->addObject3D(objId, path);
}

int OscUtil::processMessageAction(ofxOscMessage m, ISceneHandler *sceneHandler) {
    if ( m.getAddress() == "/camera/add" ) {
        OscUtil::processAddCameraMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/camera/setpos" ) {
        OscUtil::processSetCameraPosMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/camera/seteye" ) {
        OscUtil::processSetCameraEyeMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/quad/add") {
        OscUtil::processAddQuadMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/quad/setpoint" ) {
        OscUtil::processSetQuadPointMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/layer/add" ) {
        OscUtil::processAddLayerMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/camera/activate" ) {
        OscUtil::processActivateCameraMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/quad/enable" ) {
        OscUtil::processEnableQuadMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/scene/setbackground" ) {
        OscUtil::processSetBackgroundMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/group/add" ) {
        OscUtil::processAddGroupMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/group/addquad" ) {
        OscUtil::processAddQuadToGroupMsg(m, sceneHandler);
    } else if ( m.getAddress() == "/object/add" ) {
        OscUtil::processAddObject3dMsg(m, sceneHandler);
    } else {
        return -1;
    }
    return 1;
}

ofxOscMessage OscUtil::serializeEffect(Effect *ef){
    ofxOscMessage m;
    if (ef->getType() == FADE_EFFECT){
        FadeEffect *feff = (FadeEffect*) ef;
    } else if (ef->getType() == POSITION_EFFECT){
        PositionEffect *peff = (PositionEffect*) ef;
        //new PositionEffect(obj3d, ofxVec3f(0,3,0), ofxVec3f(0,-3,0), 0.5f)
    } else if (ef->getType() == TEXTURE_EFFECT){
        TextureEffect *teff = (TextureEffect*) ef;
    }
    return m;
}

Effect* OscUtil::deserializeEffect(ofxOscMessage m){
    int effType = m.getArgAsInt32(0);
    Effect *eff;
    if (effType == FADE_EFFECT){
        string groupId = m.getArgAsString(1);
        float colIniR = m.getArgAsFloat(2);
        float colIniG = m.getArgAsFloat(3);
        float colIniB = m.getArgAsFloat(4);
        float colIniA = m.getArgAsFloat(5);
        float colFinR = m.getArgAsFloat(6);
        float colFinG = m.getArgAsFloat(7);
        float colFinB = m.getArgAsFloat(8);
        float colFinA = m.getArgAsFloat(9);
        float delay = m.getArgAsFloat(10);
        //eff = new FadeEffect(new FadeEffect(groupId, ofxVec4f(colIniR,colIniG,colIniB,colIniA), ofxVec4f(colFinR,colFinG,colFinB,colFinA), delay));
    } else if (effType == POSITION_EFFECT){
        //eff = new PositionEffect(/*obj3d, ofxVec3f(0,3,0), ofxVec3f(0,-3,0), 0.5f*/);
    } else if (effType == TEXTURE_EFFECT){
        //eff = new TextureEffect();
    }
    return eff;
}

