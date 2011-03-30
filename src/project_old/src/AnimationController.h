#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <map>

#include "AnimationLoop.h"
#include "IEventListener.h"

using namespace std;

class AnimationController
{
    public:
        AnimationController();
        virtual ~AnimationController();
        //static void AddLoop(string key, AnimationLoop *anim);
        //static void PlayLoop(string key);
        static void PlayLoop(AnimationLoop *loop);
        static void Update();

    protected:
    private:
        //static map<string, AnimationLoop*> loops;
        static vector<AnimationLoop*> loops;
};

#endif // ANIMATIONCONTROLLER_H
