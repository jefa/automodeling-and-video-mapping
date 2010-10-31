#ifndef QUAD2D_H
#define QUAD2D_H

#include "IPropertyManager.h"
#include "Material.h"

#include <string>
using namespace std;

class Quad2D : public IPropertyManager
{
    public:
        Quad2D(string id);
        Quad2D(string id, float x1,float y1,float x2,float y2,float x3, float y3, float x4, float y4);
        virtual ~Quad2D();
        virtual void set(int aParam, float value);
        virtual float get(int aParam);
        void draw();
        void setPoint(int i, float x, float y);
        void getPoint(int i, float &x, float &y);
        int getControlPointAt(int x, int y);
        void setSelected(bool selected);
        void setMaterial(Material *mat);
        Material* getMaterial();
        void setEnabled(bool enabled);
        bool isEnabled();
    protected:
    private:
        float quadPoints[8];
        Material *material;
        bool selected;
        string id;
        bool enabled;
};

#endif // QUAD2D_H
