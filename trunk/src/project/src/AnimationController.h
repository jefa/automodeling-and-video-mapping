#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <vector>

#include "Animation.h"
#include "ConcatenacionAnimaciones.h"

using namespace std;

class AnimationController
{
    public:
        AnimationController();
        virtual ~AnimationController();
        void AddAnimation(Animation anim, ConcatenacionAnimaciones conc);
    protected:
    private:
        vector<Animation> animator;
        vector<Animation> colaEspera;
};

#endif // ANIMATIONCONTROLLER_H
