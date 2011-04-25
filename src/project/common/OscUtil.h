#ifndef OSCUTIL_H
#define OSCUTIL_H

#include "ofxOsc.h"
#include "ofxVec3f.h"

#include "ISceneHandler.h"
#include "Effect.h"

enum OSC_MESSAGES {
	ADD_LAYER,
	ADD_QUAD,
	REMOVE_LAYER,
	REMOVE_QUAD,
	ADD_CAMERA,
	REMOVE_CAMERA
};

class OscUtil
{
    public:
        OscUtil();
        virtual ~OscUtil();

        static ofxOscMessage createSetBackgroundMsg(int r, int g, int b);
        static void processSetBackgroundMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddCameraMsg(string id);
        static void processAddCameraMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createSetCameraPosMsg(string id, ofxVec3f position);
        static void processSetCameraPosMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createSetCameraEyeMsg(string id, ofxVec3f eye);
        static void processSetCameraEyeMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createActivateCameraMsg(string id);
        static void processActivateCameraMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddQuadMsg(string camId, string layerId, string quadId);
        static void processAddQuadMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createSetQuadPointMsg(string camId, string layerId, string quadId,
                                                   int point, float coordX, float coordY);
        static void processSetQuadPointMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createEnableQuadMsg(string camId, string layerId, string quadId, bool enabled);
        static void processEnableQuadMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddLayerMsg(string camId, string layerId);
        static void processAddLayerMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddGroupMsg(string groupId);
        static void processAddGroupMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createAddQuadToGroupMsg(string groupId, string camId, string layerId, string quadId);
        static void processAddQuadToGroupMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddObject3dMsg(string objId, string base64data);
        static void processAddObject3dMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static int processMessageAction(ofxOscMessage, ISceneHandler *);

        static ofxOscMessage serializeEffect(Effect *ef);
        static Effect* deserializeEffect(ofxOscMessage);
    protected:
    private:
};

#endif // OSCUTIL_H
