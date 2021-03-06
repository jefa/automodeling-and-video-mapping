#ifndef ANIMATION_H
#define ANIMATION_H

#include "IPropertyManager.h"

class Animation
{
    public:
        Animation(IPropertyManager *pmgr, int propertyId, double timestamp);
        virtual ~Animation();
        bool mismaAnimacion(Animation *anim);
        virtual void Update()=0;
        virtual void Start();
        virtual void End();
        bool isRunning();

    protected:
        IPropertyManager *propMgr;
        int propertyId;
        double totalElapsedTime;
        double totalAnimationTime;

    private:
        bool off;

};

#endif // ANIMATION_H
