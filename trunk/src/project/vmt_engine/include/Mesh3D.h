#ifndef MESH3D_H
#define MESH3D_H

#include "ofx3DModelLoader.h"

#include <string>
using namespace std;

class Mesh3D
{
    public:
        Mesh3D(string path);
        virtual ~Mesh3D();

        void draw();
    protected:
    private:
        ofx3DModelLoader model;
};

#endif // MESH3D_H
