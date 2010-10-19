#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <vector>

#include "Animation.h"
#include "AnimationsLinking.h"

using namespace std;

class AnimationController
{
    public:
        AnimationController();
        virtual ~AnimationController();
        void AddAnimation(Animation *anim, AnimationsLinking conc);
        void Update(unsigned int interval);

    protected:
    private:
        vector<Animation*> animator;
        vector<Animation*> colaEspera;
};

#endif // ANIMATIONCONTROLLER_H
