#ifndef LAYER2D_H
#define LAYER2D_H

#include "Quad2D.h"

#include <string>
#include <map>
using namespace std;

class Layer2D
{
    public:
        Layer2D();
        virtual ~Layer2D();

        Quad2D* addQuad2D(string id);
        Quad2D* getQuad2D(string id);

        void draw();
        void setEnabled(bool enabled);

    private:
        bool enabled;
};

#endif // LAYER2D_H
