#include "AnimationLoop.h"
#include "ofUtils.h"

AnimationLoop::AnimationLoop(string id)
{
    this->id = id;
    this->started = false;
}

AnimationLoop::~AnimationLoop()
{
    //dtor
}

void AnimationLoop::AddAnimation(Animation* anim) {
    this->animations.push_back(anim);
}

void AnimationLoop::Play() {
    started = true;

    for (unsigned int i = 0; i < animations.size(); i++) {
        Animation *anim = animations[i];
        bool isAlreadyInPlaylist = false;
        for (unsigned int j = 0; j < playable_animations.size(); j++) {
            Animation *playable = playable_animations[j];
            if (playable->mismaAnimacion(anim)) {
                isAlreadyInPlaylist = true;
                waiting_animations.push_back(anim);
                break;
            }
        }
        if(!isAlreadyInPlaylist) {
            playable_animations.push_back(anim);
        }
    }

    vector<Animation*>::iterator it;
    for(it = playable_animations.begin(); it != playable_animations.end(); ++it) {
        (*it)->Start();
    }
}

bool AnimationLoop::isStarted() {
    return started;
}

void AnimationLoop::Stop() {
}

void AnimationLoop::Update() {
    if(this->started) {
        for (unsigned int i = 0; i < playable_animations.size(); i++) {
            Animation *anim = playable_animations[i];
            anim->Update();
            if(!anim->isRunning()) {
                playable_animations.erase(playable_animations.begin() + i);

                //Busco si hay una animacion del mismo tipo esperando
                //y si encuentro una la agrego a animator y la saco de colaEspera
                for (unsigned int j = 0; j < waiting_animations.size(); j++) {
                    Animation *espera = waiting_animations[j];
                    if (espera->mismaAnimacion(anim)) {
                        playable_animations.push_back(espera);
                        espera->Start();
                        waiting_animations.erase(waiting_animations.begin() + j);
                        break;
                    }
                }
            }
        }
    }
}

void AnimationLoop::setLoopable(bool b) {
    this->loopable = b;
}
