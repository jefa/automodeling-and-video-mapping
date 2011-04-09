#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "ofMain.h"
#include "model3DS.h"

#include <vector>
#include <string>
using namespace std;

class Object3D
{
    public:
        Object3D(string path);
        virtual ~Object3D();

        void draw();

        void setPosition(float x, float y, float z);
        void setScale(float x, float y, float z);
        void setRotation(int which, float angle, float rot_x, float rot_y, float r_z);

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
