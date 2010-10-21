#ifndef ANIMATION_H
#define ANIMATION_H

#include "IPropertyManager.h"

#include <string>
using namespace std;

class Animation
{
    public:
        Animation(IPropertyManager *pmgr, string propertyId, int timeMilliseconds);
        virtual ~Animation();
        bool mismaAnimacion(Animation *anim);
        virtual void Update(int elapsedTime)=0;
        bool off;

    protected:
        IPropertyManager *propMgr;
        string propertyId;
        int totalElapsedTime;
        int totalAnimationTime;

    private:

};

#endif // ANIMATION_H
