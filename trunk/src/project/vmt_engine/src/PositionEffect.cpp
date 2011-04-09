#include "PositionEffect.h"

PositionEffect::PositionEffect(Object3D *obj, ofxVec3f posIni, ofxVec3f posFin, float delay) {
    this->object3d = obj;
    this->posIni = posIni;
    this->posFin = posFin;
    this->delay = delay;
}

PositionEffect::~PositionEffect() {
}

void PositionEffect::play() {

}
