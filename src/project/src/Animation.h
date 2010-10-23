#ifndef ANIMATION_H
#define ANIMATION_H

#include "IPropertyManager.h"

class Animation
{
    public:
        Animation(IPropertyManager *pmgr, int propertyId, int timeMilliseconds);
        virtual ~Animation();
        bool mismaAnimacion(Animation *anim);
        virtual void Update(int elapsedTime)=0;
        bool off;

    protected:
        IPropertyManager *propMgr;
        int propertyId;
        int totalElapsedTime;
        int totalAnimationTime;

    private:

};

#endif // ANIMATION_H
