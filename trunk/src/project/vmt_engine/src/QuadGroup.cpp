#include "QuadGroup.h"

QuadGroup::QuadGroup(string name) {
    this->name = name;
}

QuadGroup::~QuadGroup() {
    //dtor
}

void QuadGroup::addQuad2D(Quad2D* quad) {
    quads2D.push_back(quad);

    //Expandir si corresponde el contenedor
}

void QuadGroup::genUVWCoords() {
    vector<Quad2D*>::iterator quadsIt;
    //Case FaceMap
    for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        (*quadsIt)->setUVCoordinate(0, 0,0);
        (*quadsIt)->setUVCoordinate(1, 1,0);
        (*quadsIt)->setUVCoordinate(2, 1,1);
        (*quadsIt)->setUVCoordinate(3, 0,1);
    }
}

float QuadGroup::get(int aParam) {
    if(!quads2D.empty())
        return (*(quads2D.begin()))->get(aParam);
    else
        return 0;
}

void QuadGroup::SetTextureParams(string key, textureType type) {
    vector<Quad2D*>::iterator quadsIt;
    for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        (*quadsIt)->getMaterial()->SetTextureParams(key, type);
    }
}

void QuadGroup::set(int aParam, float aValue) {
    switch(aParam) {
        case AMBIENT_R:
        case AMBIENT_G:
        case AMBIENT_B:
        case AMBIENT_A:
            vector<Quad2D*>::iterator quadsIt;
            for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
                (*quadsIt)->set(aParam, aValue);
            }
            break;
    }
}
