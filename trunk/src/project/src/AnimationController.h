#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <map>

#include "AnimationLoop.h"
#include "AnimEventArg.h"
#include "IEventListener.h"

using namespace std;

class AnimationController : public IEventListener
{
    public:
        AnimationController();
        virtual ~AnimationController();
        void AddLoop(string key, AnimationLoop *anim);
        void PlayLoop(string key);
        void Update(double timestamp);
        void event(EventArg *e);

    protected:
    private:
        map<string, AnimationLoop*> loops;
};

#endif // ANIMATIONCONTROLLER_H
