#ifndef QUAD2D_H
#define QUAD2D_H

#include "IPropertyManager.h"
#include "ofxVectorMath.h"

#include <string>
using namespace std;

enum A_PARAM_QUAD2D {COL_R, COL_G, COL_B, COL_A};

class Quad2D : public IPropertyManager
{
    public:
        Quad2D(float x1 = 100.0f, float y1 = 100.0f, float x2 = 300.0f, float y2 = 100.0f,
               float x3 = 300.0f, float y3 = 300.0f, float x4 = 100.0f, float y4 = 300.0f);

        virtual ~Quad2D();
        virtual void set(int aParam, float value);
        virtual float get(int aParam);
        void draw();
        void setPoint(int i, float x, float y);
        void getPoint(int i, float &x, float &y);
        void setUVCoordinate(int i, float u, float v);
        int getControlPointAt(int x, int y);
        void setSelected(bool selected);
        void setEnabled(bool enabled);
        bool isEnabled();
        void setId(string id);
        string getId();
    protected:
    private:
        float quadPoints[8];
        float quadTextCoords[8];
        bool selected;
        bool enabled;
        string id;
        ofxVec4f color;

};

#endif // QUAD2D_H
