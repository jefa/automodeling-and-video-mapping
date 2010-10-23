#ifndef QUAD2D_H
#define QUAD2D_H

#include "IPropertyManager.h"

class Quad2D : public IPropertyManager
{
    public:
        Quad2D(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4);
        virtual ~Quad2D();
        virtual void set(int aParam, float value);
        virtual float get(int aParam);
        void draw();
    protected:
    private:
        ofPoint p1;
        ofPoint p2;
        ofPoint p3;
        ofPoint p4;
};

#endif // QUAD2D_H
