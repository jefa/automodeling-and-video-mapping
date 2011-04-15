#ifndef TEXTUREEFFECT_H
#define TEXTUREEFFECT_H

#include "Effect.h"
#include "QuadGroup.h"
//#include "AnimationManager.h"
//#include "LinearAnimation.h"

class TextureEffect : public Effect
{
    public:
        TextureEffect(QuadGroup *qg, string textureKey, string texturePath, textureType type);
        virtual ~TextureEffect();

        virtual void play();
        virtual void test();
    protected:
    private:
        QuadGroup* group;
        string textureKey;
        textureType type;
};

#endif // TEXTUREEFFECT_H
