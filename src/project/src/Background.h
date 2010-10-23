#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "IPropertyManager.h"
#include "ofTypes.h"

enum A_PARAM_BACKGROUND {COLOR_R, COLOR_G, COLOR_B};

class Background : public IPropertyManager
{
    public:
        Background();
        virtual ~Background();

        virtual void set(int aParam, float value);
        virtual float get(int aParam);

    private:
        ofColor color;
};

#endif // BACKGROUND_H
