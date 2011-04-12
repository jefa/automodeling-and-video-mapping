#ifndef FADEEFFECT_H
#define FADEEFFECT_H

#include "Effect.h"


class FadeEffect : public Effect
{
    public:
        FadeEffect();
        virtual ~FadeEffect();

        virtual void play();
        virtual void test();
    protected:
    private:

};

#endif // FADEEFFECT_H
