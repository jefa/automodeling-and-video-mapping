#include "LinearAnimation.h"
#include <iostream>
using namespace std;

LinearAnimation::LinearAnimation(IPropertyManager *pmgr, string propertyId, int timeMilliseconds, float targetValue)
:Animation(pmgr,propertyId,timeMilliseconds)
{
    //ctor
    targetVal = targetValue;
}

float initValue = 100.0f;

void LinearAnimation::Update(int elapsedTime)
{
    this->totalElapsedTime += elapsedTime;
    float actualValue = initValue + ((float)(totalElapsedTime)/totalAnimationTime) * (targetVal - initValue);
    this->propMgr->set(propertyId, actualValue);
}

LinearAnimation::~LinearAnimation()
{
    //dtor
}
