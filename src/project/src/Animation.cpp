#include "Animation.h"

Animation::Animation(IPropertyManager *pmgr, string propId, int timeMilliseconds)
{
    propMgr = pmgr;
    propertyId = propId;
    totalElapsedTime = 0;
    totalAnimationTime = timeMilliseconds;
}

Animation::~Animation()
{
    //dtor
}

bool Animation::isOff()
{
    return off;
}

bool Animation::mismaAnimacion(Animation *anim)
{
    return (propMgr == anim->propMgr && propertyId == anim->propertyId);
}
