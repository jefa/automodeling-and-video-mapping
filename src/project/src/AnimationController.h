#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <vector>

#include "Animation.h"
#include "AnimEventArg.h"
#include "IEventListener.h"

using namespace std;

enum AnimationsLinking {IMMEDIATE, WAITEND};

class AnimationController : public IEventListener
{
    public:
        AnimationController();
        virtual ~AnimationController();
        void AddAnimation(Animation *anim, AnimationsLinking conc);
        void Update(double timestamp);
        bool Animate(string animName);
        void event(EventArg *e);

    protected:
    private:
        vector<Animation*> animator;
        vector<Animation*> colaEspera;
};

#endif // ANIMATIONCONTROLLER_H
