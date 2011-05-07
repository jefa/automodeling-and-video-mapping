#ifndef VMTMODEL_H
#define VMTMODEL_H

#include "Scene.h"
#include "OscManager.h"
#include "TimeManager.h"
#include "ISceneHandler.h"
#include "ofxXmlSettings.h"

class VmtModel : public ISceneHandler
{
    public:
        VmtModel();
        ~VmtModel();

        Scene* getScene();

        void draw();
        void update();

        void addNetNode(string nodeId, string address, int port, bool isActive, string camId);

        void setBackground(float, float, float);

        void addCamera(string id);
        void setCameraPos(string camId, float x, float y, float z);
        void setCameraEye(string camId, float x, float y, float z);
        void activateCamera(string camId);
        ofxCamera* getActiveCamera();

        void addGroup(string groupId);
        QuadGroup* getGroup(string groupId);
        map<string, QuadGroup*> getGroups();

        void addLayer(string camId, string layerId);
        void addQuad(string camId, string layerId, string quadId);
        void addQuadToGroup(string groupId, string camId, string layerId, string quadId);
        void enableQuad(string camId, string layerId, string quadId, bool enabled);
        void setQuadPoint(string camId, string layerId, string quadId,
                  int point, float coordX, float coordY);
        void addObject3D(string objId, string path);
        Object3D* getObject3D(string objId);
        Layer2D* getLayer2D(string layId);
        void addPositionEffect(string effectId, string objId, ofxVec3f posIni, ofxVec3f posFin, float delay);
        void addFadeEffect(string effectId, string groupId, ofxVec4f colorIni, ofxVec4f colorFin, float delay);
        void addTextureObjectEffect(string effectId, string objId, string facesId, string texturePath, textureType type);
        void addTextureGroupEffect(string effectId, string groupId, string texturePath, textureType type);

        void testEffect(string id);

        void scheduleEvent(float time, string effectId);
        void startTimeManager(TIMER_MODE mode);

        void addLight(string lightId);
        ofxLight* getLight(string lightId);
        void setLightSpecular(string lightId, float r, float g, float b);
        void setLightDirectional(string lightId, float r, float g, float b,
                                           float nx, float ny, float nz);
        void setLightSpot(string lightId, float r, float g, float b,
                                           float x, float y, float z,
                                           float nx, float ny, float nz,
                                           float angle, float concentration);
        void setLightPoint(string lightId, float r, float g, float b,
                                           float x, float y, float z);

        void OrbitActiveCamera(int dx, int dy);
        void RollActiveCamera(int dx);
        void DollyActiveCamera(int dy);
        void PanActiveCamera(int dx, int dy);

        void saveShow(string filepath);
        void loadShow(string filepath);

        map<string, ofxCamera*> getCameras();
        map<string, Object3D*> getObjects3D();
        map<string, Effect*> getEffects();

    protected:
        string getNodeForCamera(string camId);

    private:
        map<string, Node> network;
        Scene *scene;
        OscManager *oscManager;
        TimeManager* timeManager;

        ofxXmlSettings showXML;
};

#endif // VMTMODEL_H
