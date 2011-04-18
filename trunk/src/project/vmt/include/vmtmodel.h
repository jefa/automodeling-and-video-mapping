#ifndef VMTMODEL_H
#define VMTMODEL_H

#include "Scene.h"

class VmtModel
{
    public:
        VmtModel();
        ~VmtModel();

        Scene* getScene();

        void draw();
        void update();

        void setBackground(int, int, int);

        void addCamera(string id);
        void setCameraPos(string camId, float x, float y, float z);
        void setCameraEye(string camId, float x, float y, float z);
        void activateCamera(string camId);
        ofxCamera* getActiveCamera();

        void addGroup(string groupId);
        QuadGroup* getGroup(string groupId);

        void addLayer(string camId, string layerId);
        void addQuad(string camId, string layerId, string quadId);
        void addQuadToGroup(string groupId, string camId, string layerId, string quadId);
        void enableQuad(string camId, string layerId, string quadId, bool enabled);
        void setQuadPoint(string camId, string layerId, string quadId,
                  int point, float coordX, float coordY);
        void addObject3D(string objId, string path);
        Object3D* getObject3D(string objId);

        void addEffect(string effectId, Effect *ef);
        void testEffect(string id);

        void addLight(string lightId);
        void setLightSpecular(string lightId, float r, float g, float b);
        void setLightDirectional(string lightId, float r, float g, float b,
                                           float nx, float ny, float nz);
        void setLightSpot(string lightId, float r, float g, float b,
                                           float x, float y, float z,
                                           float nx, float ny, float nz,
                                           float angle, float concentration);
        void setLightPoint(string lightId, float r, float g, float b,
                                           float x, float y, float z);

    protected:

    private:
        Scene *scene;

};

#endif // VMTMODEL_H
