#include "LinearAnimation.h"
#include <iostream>
using namespace std;

LinearAnimation::LinearAnimation(IPropertyManager *pmgr, string propertyId, int timeMilliseconds, float targetValue)
:Animation(pmgr,propertyId,timeMilliseconds)
{
    //ctor
    targetVal = targetValue;
}

float initValue;
bool initialized = false;

void LinearAnimation::Update(int elapsedTime)
{
    if(!initialized)
    {
        initialized = true;
        initValue = this->propMgr->get(propertyId);
        this->off = false;
    }
    this->totalElapsedTime += elapsedTime;
    float actualValue = initValue + ((float)(totalElapsedTime)/totalAnimationTime) * (targetVal - initValue);
    this->propMgr->set(propertyId, actualValue);
}

LinearAnimation::~LinearAnimation()
{
    //dtor
}
