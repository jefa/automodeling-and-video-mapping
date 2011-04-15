#include "FadeEffect.h"

FadeEffect::FadeEffect(QuadGroup *qg, ofxVec4f colorIni, ofxVec4f colorFin, float delay) {
    this->group = qg;
    this->colorIni = colorIni;
    this->colorFin = colorFin;
    this->delay = delay;
}

FadeEffect::~FadeEffect() {
}

void FadeEffect::play() {
    this->group->set(AMBIENT_R, colorIni.x);
    this->group->set(AMBIENT_G, colorIni.y);
    this->group->set(AMBIENT_B, colorIni.z);
    this->group->set(AMBIENT_A, colorIni.w);

    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_R, this->delay, this->colorFin.x));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_G, this->delay, this->colorFin.y));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_B, this->delay, this->colorFin.z));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_A, this->delay, this->colorFin.w));
}

void FadeEffect::test() {
    this->group->set(AMBIENT_R, colorIni.x);
    this->group->set(AMBIENT_G, colorIni.y);
    this->group->set(AMBIENT_B, colorIni.z);
    this->group->set(AMBIENT_A, colorIni.w);

    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_R, this->delay, this->colorFin.x));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_G, this->delay, this->colorFin.y));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_B, this->delay, this->colorFin.z));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_A, this->delay, this->colorFin.w));
}
