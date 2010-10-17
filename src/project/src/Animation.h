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
        bool mismaAnimacion(Animation anim);

    protected:
        IPropertyManager *propMgr;
        string propertyId;
        int totalElapsedTime;
        int totalAnimationTime;

    private:

};

#endif // ANIMATION_H
