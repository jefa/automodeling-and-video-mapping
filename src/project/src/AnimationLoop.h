#ifndef ANIMATIONLOOP_H
#define ANIMATIONLOOP_H

#include "Animation.h"

#include <vector>
#include <string>
using namespace std;

class AnimationLoop
{
    public:
        AnimationLoop(string id);
        virtual ~AnimationLoop();
        void AddAnimation(Animation* anim);
        void Play();
        void Stop();
        void Update(double timestamp);
        void setLoopable(bool);
        bool isStarted();
    protected:
    private:
        string id;
        bool loopable;
        bool started;
        vector<Animation*> animations;
        vector<Animation*> playable_animations;
        vector<Animation*> waiting_animations;

};

#endif // ANIMATIONLOOP_H
