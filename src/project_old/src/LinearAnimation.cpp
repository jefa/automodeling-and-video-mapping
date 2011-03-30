#include "ofAppRunner.h"

#include "LinearAnimation.h"
#include <iostream>
using namespace std;

LinearAnimation::LinearAnimation(IPropertyManager *pmgr, int propertyId, double timestamp, float targetValue)
:Animation(pmgr, propertyId, timestamp)
{
    //ctor
    targetVal = targetValue;
}

void LinearAnimation::Start()
{
    Animation::Start();
    initValue = this->propMgr->get(propertyId);
}

void LinearAnimation::End()
{
    Animation::End();
}

void LinearAnimation::Update()
{
    float timestamp = ofGetLastFrameTime();
    if(!isRunning()){
        return;
    }

    this->totalElapsedTime += timestamp;
    float actualValue = initValue + (totalElapsedTime/totalAnimationTime) * (targetVal - initValue);

    this->propMgr->set(propertyId, actualValue);

    if (totalElapsedTime >= totalAnimationTime)
    {
        this->End();
    }
}

LinearAnimation::~LinearAnimation()
{
    //dtor
}
