#ifndef LINEARANIMATION_H
#define LINEARANIMATION_H

#include "Animation.h"
#include <string>
using namespace std;

class LinearAnimation : public Animation
{
    public:
        LinearAnimation(IPropertyManager *pmgr, string propertyId, int timeMilliseconds, float targetValue);
        virtual ~LinearAnimation();
        virtual void Update(int elapsedTime);
    protected:
    private:
        float targetVal;
};

#endif // LINEARANIMATION_H
