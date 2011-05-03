#ifndef FADEEFFECT_H
#define FADEEFFECT_H

#include "Effect.h"
#include "QuadGroup.h"
#include "AnimationManager.h"
#include "LinearAnimation.h"

class FadeEffect : public Effect
{
    public:
        FadeEffect(string id, QuadGroup *qg, ofxVec4f colorIni, ofxVec4f colorFin, float delay);
        virtual ~FadeEffect();

        virtual void play();
        virtual void test();
        virtual int getType();
        virtual const char* toString();

        QuadGroup* getQuadGroup();
        void setQuadGroup(QuadGroup*);
        ofxVec4f getColorIni();
        void setColorIni(ofxVec4f);
        ofxVec4f getColorFin();
        void setColorFin(ofxVec4f);
        float getDelay();
        void setDelay(float);

        virtual SerializedNode* Serialize();
    protected:
    private:
        QuadGroup *group;
        ofxVec4f colorIni;
        ofxVec4f colorFin;
        float delay;

};

#endif // FADEEFFECT_H
