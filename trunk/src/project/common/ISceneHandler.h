#ifndef ISCENEHANDLER_H_INCLUDED
#define ISCENEHANDLER_H_INCLUDED

#include "Scene.h"

class ISceneHandler
{
    public:
        virtual void setBackground(int, int, int) =0;

        virtual void addCamera(string id) =0;
        virtual void setCameraPos(string camId, float x, float y, float z) =0;
        virtual void setCameraEye(string camId, float x, float y, float z) =0;
        virtual void activateCamera(string camId) =0;
        virtual ofxCamera* getActiveCamera() =0;

        virtual void addGroup(string groupId) =0;
        virtual QuadGroup* getGroup(string groupId) =0;

        virtual void addLayer(string camId, string layerId) =0;
        virtual void addQuad(string camId, string layerId, string quadId) =0;
        virtual void addQuadToGroup(string groupId, string camId, string layerId, string quadId) =0;
        virtual void enableQuad(string camId, string layerId, string quadId, bool enabled) =0;
        virtual void setQuadPoint(string camId, string layerId, string quadId,
                  int point, float coordX, float coordY) =0;
        virtual void addObject3D(string objId, string path) =0;
        virtual Object3D* getObject3D(string objId) =0;

        virtual void addEffect(string effectId, Effect *ef) =0;
        virtual void testEffect(string id) =0;

        virtual void addLight(string lightId) =0;
        virtual void setLightSpecular(string lightId, float r, float g, float b) =0;
        virtual void setLightDirectional(string lightId, float r, float g, float b,
                                           float nx, float ny, float nz) =0;
        virtual void setLightSpot(string lightId, float r, float g, float b,
                                           float x, float y, float z,
                                           float nx, float ny, float nz,
                                           float angle, float concentration) =0;
        virtual void setLightPoint(string lightId, float r, float g, float b,
                                           float x, float y, float z) =0;
};

#endif // ISCENEHANDLER_H_INCLUDED
