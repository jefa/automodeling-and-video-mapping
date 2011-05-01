#include "PositionEffect.h"
#include "AnimationManager.h"
#include "LinearAnimation.h"
#include "IPropertyManager.h"

PositionEffect::PositionEffect(string id, Object3D *obj, ofxVec3f posIni, ofxVec3f posFin, float delay) {
    this->id = id;
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

int PositionEffect::getType(){
    return POSITION_EFFECT;
}

Object3D* PositionEffect::getObject3D(){
    return this->object3d;
}

ofxVec3f PositionEffect::getPosIni(){
    return this->posIni;
}

ofxVec3f PositionEffect::getPosFin(){
    return this->posFin;
}

float PositionEffect::getDelay(){
    return this->delay;
}

const char* PositionEffect::toString(){
    string txt = "PositionEffect::"+object3d->getId();//+"::"+posIni+"::"+posFin+"::"+delay;
    return txt.c_str();
}

SerializedNode* PositionEffect::Serialize() {
    SerializedNode *node = new SerializedNode("effect");
    node->addAttribute("id", this->id);
    node->addAttribute("type", "position");
    node->addAttribute("objid", this->object3d->getId());

    node->addAttribute("pos1", this->posIni);
    node->addAttribute("pos2", this->posFin);

    node->addAttribute("delay", this->delay);
    return node;
}
