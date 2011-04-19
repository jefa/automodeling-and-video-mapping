#include "OscUtil.h"

OscUtil::OscUtil()
{
    //ctor
}

OscUtil::~OscUtil()
{
    //dtor
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

ofxOscMessage OscUtil::createAddQuadMsg(string camId, string layerId, string quadId) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/quad/add");
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    return oscMessage;
}

ofxOscMessage OscUtil::createSetQuadPointMsg(string camId, string layerId, string quadId,
                                           int point, float coordX, float coordY){
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/quad/add");
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    oscMessage.addIntArg(point);
    oscMessage.addFloatArg(coordX);
    oscMessage.addFloatArg(coordY);
    return oscMessage;
}

ofxOscMessage OscUtil::createAddLayerMsg(string camId, string layerId) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress("/layer/add");
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    return oscMessage;
}

/*void OscUtil::parseMessage() {
    throw new UnsupportedOperationException("The method is not implemented yet.");
}*/

int OscUtil::getMessageAction(ofxOscMessage msg) {
    //throw new UnsupportedOperationException("The method is not implemented yet.");
    return -1;
}
