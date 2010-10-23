#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <vector>

#include "Animation.h"

using namespace std;

enum AnimationsLinking {IMMEDIATE, WAITEND};

class AnimationController
{
    public:
        AnimationController();
        virtual ~AnimationController();
        void AddAnimation(Animation *anim, AnimationsLinking conc);
        void Update(double timestamp);

    protected:
    private:
        vector<Animation*> animator;
        vector<Animation*> colaEspera;
};

#endif // ANIMATIONCONTROLLER_H
