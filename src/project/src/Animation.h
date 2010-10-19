#ifndef ANIMATION_H
#define ANIMATION_H

#include "propertyManager.h"

#include <string>
using namespace std;

class Animation
{
    public:
        Animation(IPropertyManager *pmgr, string propertyId, int timeMilliseconds);
        virtual ~Animation();
        bool mismaAnimacion(Animation *anim);
        virtual void Update(int elapsedTime)=0;
        bool isOff();

    protected:
        IPropertyManager *propMgr;
        string propertyId;
        int totalElapsedTime;
        int totalAnimationTime;

    private:
        bool off;

};

#endif // ANIMATION_H
