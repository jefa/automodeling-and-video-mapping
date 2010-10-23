#ifndef LINEARANIMATION_H
#define LINEARANIMATION_H

#include "Animation.h"

class LinearAnimation : public Animation
{
    public:
        LinearAnimation(IPropertyManager *pmgr, int propertyId, int timeMilliseconds, float targetValue);
        virtual ~LinearAnimation();
        virtual void Update(int elapsedTime);
    protected:
    private:
        float targetVal;
};

#endif // LINEARANIMATION_H
