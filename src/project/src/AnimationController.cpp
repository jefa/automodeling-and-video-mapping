#include "AnimationController.h"
#include <iostream>
using namespace std;

map<string, AnimationLoop*> AnimationController::loops;

AnimationController::AnimationController()
{
    //ctor
}

AnimationController::~AnimationController()
{
    //dtor
}

void AnimationController::AddLoop(string key, AnimationLoop *anim) {
    loops.insert(pair<string, AnimationLoop*>(key, anim));
}

void AnimationController::PlayLoop(string key) {
    loops[key]->Play();
}

void AnimationController::Update()
{
    map<string, AnimationLoop*>::iterator it;
    for(it = loops.begin(); it != loops.end(); ++it) {
        if((*it).second->isStarted()) {
            (*it).second->Update();
        }
    }
}

void AnimationController::event(EventArg *e)
{
    AnimEventArg *animEvent = (AnimEventArg*) e;
    if (animEvent->isActivate)
    {
        //this->Animate(animEvent->source);
    }
}
