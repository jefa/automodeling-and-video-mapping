#ifndef OSCUTIL_H
#define OSCUTIL_H

#include "ofxOsc.h"
#include "ofxVec3f.h"

#include "ISceneHandler.h"
#include "Effect.h"

const string LAYER_ADD_ADDR             = "/layer/add";
const string CAMERA_ADD_ADDR            = "/camera/add";
const string CAMERA_SETPOS_ADDR         = "/camera/setpos";
const string CAMERA_SETEYE_ADDR         = "/camera/seteye";
const string CAMERA_ACTIVATE_ADDR       = "/camera/activate";
const string QUAD_ADD_ADDR              = "/quad/add";
const string QUAD_SETPOINT_ADDR         = "/quad/setpoint";
const string QUAD_ENABLE_ADDR           = "/quad/enable";
const string SCENE_BACKGROUND_ADDR      = "/scene/setbackground";
const string GROUP_ADD_ADDR             = "/group/add";
const string GROUP_ADDQUAD_ADDR         = "/group/addquad";
const string OBJECT_ADD_ADDR            = "/object/add";
const string EFFECT_ADD_FADE_ADDR       = "/effect/add_fade";
const string EFFECT_ADD_POSITION_ADDR   = "/effect/add_position";
const string EFFECT_TEST_ADDR           = "/effect/test";
const string LIGHT_ADD_ADDR             = "/light/add";
const string LIGHT_SPECULAR_ADDR        = "/light/specular";
const string LIGHT_DIRECTIONAL_ADDR     = "/light/directional";
const string LIGHT_SPOT_ADDR            = "/light/spot";
const string LIGHT_POINT_ADDR           = "/light/point";

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

        static ofxOscMessage createAddPositionEffectMsg(string effectId, string objId, ofxVec3f posIni,
                                                        ofxVec3f posFin, float delay);
        static void processAddPositionEffectMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createAddFadeEffectMsg(string effectId, string groupId, ofxVec4f colorIni,
                                                    ofxVec4f colorFin, float delay);
        static void processAddFadeEffectMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createTestEffectMsg(string effectId);
        static void processTestEffectMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddLightMsg(string lightId);
        static void processAddLightMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createLightSpecularMsg(string lightId, float r, float g, float b);
        static void processLightSpecularMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createLightDirectionalMsg(string lightId, float r, float g, float b, float nx, float ny, float nz);
        static void processLightDirectionalMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createLightSpotMsg(string lightId, float r, float g, float b, float x, float y, float z, float nx,
                           float ny, float nz, float angle, float concentration);
        static void processLightSpotMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createLightPointMsg(string lightId, float r, float g, float b, float x, float y, float z);
        static void processLightPointMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static int processMessageAction(ofxOscMessage, ISceneHandler *);

    protected:
    private:
};

#endif // OSCUTIL_H
