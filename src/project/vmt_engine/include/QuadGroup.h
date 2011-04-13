#ifndef QUADGROUP_H
#define QUADGROUP_H

#include "Quad2D.h"

#include <string>
#include <map>
using namespace std;

class QuadGroup : public IPropertyManager
{
    public:
        QuadGroup(string name);
        virtual ~QuadGroup();

        void addQuad2D(Quad2D* quad);
        void genUVWCoords();

        virtual float get(int aParam);
        virtual void set(int aParam, float aValue);
    protected:
    private:
        string name;
        bool enabled;
        map<string, Quad2D*> quads2D;
};

#endif // QUADGROUP_H
