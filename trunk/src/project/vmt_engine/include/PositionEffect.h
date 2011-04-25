#ifndef POSITIONEFFECT_H
#define POSITIONEFFECT_H

#include "Effect.h"
#include "Object3D.h"
#include "ofxVectorMath.h"

class PositionEffect : public Effect
{
    public:
        PositionEffect(Object3D *obj, ofxVec3f posIni, ofxVec3f posFin, float delay);
        virtual ~PositionEffect();

        virtual void play();
        virtual void test();
        virtual int getType();

        Object3D* getObject3D();
        ofxVec3f getPosIni();
        ofxVec3f getPosFin();
        float getDelay();

    protected:
    private:
        Object3D *object3d;
        ofxVec3f posIni;
        ofxVec3f posFin;
        float delay;
};

#endif // POSITIONEFFECT_H