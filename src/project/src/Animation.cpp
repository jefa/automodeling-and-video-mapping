#include "Animation.h"

Animation::Animation(IPropertyManager *pmgr, int propId, double timestamp)
{
    propMgr = pmgr;
    propertyId = propId;
    totalElapsedTime = 0;
    totalAnimationTime = timestamp;
    off = true;
}

void Animation::Start()
{
    off = false;
}

void Animation::End()
{
    off = true;
}

bool Animation::isStarted()
{
    return !off;
}

bool Animation::isEnded()
{
    return off;
}

Animation::~Animation()
{
    //dtor
}

bool Animation::mismaAnimacion(Animation *anim)
{
    return (propMgr == anim->propMgr && propertyId == anim->propertyId);
}
