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
    this->group->set(COL_R, colorIni.x);
    this->group->set(COL_G, colorIni.y);
    this->group->set(COL_B, colorIni.z);
    this->group->set(COL_A, colorIni.w);

    AnimationManager::PlayAnimation(new LinearAnimation(this->group, COL_R, this->delay, this->colorFin.x));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, COL_G, this->delay, this->colorFin.y));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, COL_B, this->delay, this->colorFin.z));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, COL_A, this->delay, this->colorFin.w));
}

void FadeEffect::test() {
    this->group->set(COL_R, colorIni.x);
    this->group->set(COL_G, colorIni.y);
    this->group->set(COL_B, colorIni.z);
    this->group->set(COL_A, colorIni.w);

    AnimationManager::PlayAnimation(new LinearAnimation(this->group, COL_R, this->delay, this->colorFin.x));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, COL_G, this->delay, this->colorFin.y));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, COL_B, this->delay, this->colorFin.z));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, COL_A, this->delay, this->colorFin.w));
}
