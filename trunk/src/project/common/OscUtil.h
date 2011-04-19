#ifndef OSCUTIL_H
#define OSCUTIL_H

#include "ofxOsc.h"
#include "ofxVec3f.h"

#include "ISceneHandler.h"

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

        static ofxOscMessage createAddCameraMsg(string id);
        static ofxOscMessage createSetCameraPosMsg(string id, ofxVec3f position);
        static ofxOscMessage createSetCameraEyeMsg(string id, ofxVec3f eye);

        static void processAddCameraMsg(ofxOscMessage msg, ISceneHandler* sceneHandler);

        static ofxOscMessage createAddQuadMsg(string camId, string layerId, string quadId);
        static ofxOscMessage createSetQuadPointMsg(string camId, string layerId, string quadId,
                                                   int point, float coordX, float coordY);

        static ofxOscMessage createAddLayerMsg(string camId, string layerId);

        //static void parseMessage();
        int getMessageAction(ofxOscMessage);

    protected:
    private:
};

#endif // OSCUTIL_H

