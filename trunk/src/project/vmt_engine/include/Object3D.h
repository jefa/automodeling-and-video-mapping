#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "ofMain.h"
#include "model3DS.h"
#include "IPropertyManager.h"

#include <vector>
#include <string>
using namespace std;

enum A_PARAM_OBJECT3D {POS_X, POS_Y, POS_Z};

class Object3D : public IPropertyManager
{
    public:
        Object3D(string path);
        virtual ~Object3D();

        void draw();

        void setPosition(float x, float y, float z);
        void setScale(float x, float y, float z);
        void setRotation(int which, float angle, float rot_x, float rot_y, float r_z);

        virtual float get(int aParam);
        virtual void set(int aParam, float aValue);

    protected:
    private:
        vector <float> rotAngle;
        vector <ofPoint> rotAxis;
        ofPoint scale;
        ofPoint pos;

        int numRotations;
        model3DS * model;

};

#endif // MESH3D_H
