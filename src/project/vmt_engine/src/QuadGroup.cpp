#include "QuadGroup.h"

QuadGroup::QuadGroup(string name) {
    this->name = name;
}

QuadGroup::~QuadGroup() {
    //dtor
}

void QuadGroup::addQuad2D(Quad2D* quad) {
    quads2D.insert(pair<string, Quad2D*>(quad->getName(), quad));

    //Expandir si corresponde el contenedor
}

void QuadGroup::genUVWCoords() {

    //Case FaceMap
    for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        quadsIt->second->setUVCoordinate(0, 0,0);
        quadsIt->second->setUVCoordinate(1, 1,0);
        quadsIt->second->setUVCoordinate(2, 1,1);
        quadsIt->second->setUVCoordinate(3, 0,1);
    }
}

float QuadGroup::get(int aParam) {
    return 0;
}

void QuadGroup::set(int aParam, float aValue) {
    for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        quadsIt->second->set(aParam, aValue);
    }
}
