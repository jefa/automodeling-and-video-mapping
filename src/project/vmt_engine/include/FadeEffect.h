#ifndef FADEEFFECT_H
#define FADEEFFECT_H

#include "Effect.h"
#include "QuadGroup.h"
#include "AnimationManager.h"
#include "LinearAnimation.h"

class FadeEffect : public Effect
{
    public:
        FadeEffect(QuadGroup *qg, ofxVec4f colorIni, ofxVec4f colorFin, float delay);
        virtual ~FadeEffect();

        virtual void play();
        virtual void test();
        virtual int getType();

        QuadGroup* getQuadGroup();
        ofxVec4f getColorIni();
        ofxVec4f getColorFin();
        float getDelay();

    protected:
    private:
        QuadGroup *group;
        ofxVec4f colorIni;
        ofxVec4f colorFin;
        float delay;

};

#endif // FADEEFFECT_H
