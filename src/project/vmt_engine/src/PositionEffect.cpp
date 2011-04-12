#include "PositionEffect.h"
#include "AnimationManager.h"
#include "LinearAnimation.h"
#include "IPropertyManager.h"

PositionEffect::PositionEffect(Object3D *obj, ofxVec3f posIni, ofxVec3f posFin, float delay) {
    this->object3d = obj;
    this->posIni = posIni;
    this->posFin = posFin;
    this->delay = delay;
}

PositionEffect::~PositionEffect() {
}

void PositionEffect::play() {
    this->object3d->setPosition(posIni.x, posIni.y, posIni.z);

    AnimationManager::PlayAnimation(new LinearAnimation(this->object3d, POS_X, this->delay, this->posFin.x));
    AnimationManager::PlayAnimation(new LinearAnimation(this->object3d, POS_Y, this->delay, this->posFin.y));
    AnimationManager::PlayAnimation(new LinearAnimation(this->object3d, POS_Z, this->delay, this->posFin.z));
}

void PositionEffect::test() {
    this->object3d->setPosition(posIni.x, posIni.y, posIni.z);

    AnimationManager::PlayAnimation(new LinearAnimation(this->object3d, POS_X, this->delay, this->posFin.x));
    AnimationManager::PlayAnimation(new LinearAnimation(this->object3d, POS_Y, this->delay, this->posFin.y));
    AnimationManager::PlayAnimation(new LinearAnimation(this->object3d, POS_Z, this->delay, this->posFin.z));
}
