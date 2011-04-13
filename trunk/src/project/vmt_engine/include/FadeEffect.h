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
    protected:
    private:
        QuadGroup *group;
        ofxVec4f colorIni;
        ofxVec4f colorFin;
        float delay;

};

#endif // FADEEFFECT_H
