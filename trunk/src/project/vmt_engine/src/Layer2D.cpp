#include "Layer2D.h"

map<string, Quad2D*>::iterator quadsIt;

Layer2D::Layer2D()
{
    this->enabled = true;
}

Layer2D::Layer2D(string name){
    this->enabled = true;
    this->name = name;
}

Layer2D::~Layer2D()
{
    //dtor
}

Quad2D* Layer2D::addQuad2D(string id) {
    Quad2D* quad2D = new Quad2D();
    quad2D->setId(id);
    quads2D.insert(pair<string, Quad2D*>(id, quad2D));
    return quad2D;
}

Quad2D* Layer2D::getQuad2D(string id) {
    return quads2D[id];
}

void Layer2D::setEnabled(bool enabled) {
    this->enabled = enabled;
}

void Layer2D::setName(string name){
    this->name = name;
}

bool Layer2D::isEnabled(){
    return enabled;
}

string Layer2D::getName(){
    return this->name;
}

map<string, Quad2D*> Layer2D::getQuads2D() {
    return quads2D;
}

void Layer2D::draw() {
    if(!enabled)
        return;

    for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        quadsIt->second->draw();
    }
}
