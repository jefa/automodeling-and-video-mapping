#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "IPropertyManager.h"
#include "ofTypes.h"

class Background : public IPropertyManager
{
    public:
        Background();
        virtual ~Background();

        virtual void set(string aParam, float value);
        virtual float get(string aParam);

    private:
        ofColor color;
};

#endif // BACKGROUND_H
