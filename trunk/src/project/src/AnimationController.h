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
        static void AddLoop(string key, AnimationLoop *anim);
        static void PlayLoop(string key);
        static void Update();
        void event(EventArg *e);

    protected:
    private:
        static map<string, AnimationLoop*> loops;
};

#endif // ANIMATIONCONTROLLER_H
