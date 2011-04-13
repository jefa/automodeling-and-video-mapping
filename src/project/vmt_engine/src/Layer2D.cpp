#include "Layer2D.h"

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
    quads2D.push_back(quad2D);
    return quad2D;
}

Quad2D* Layer2D::getQuad2D(string id) {
    vector<Quad2D*>::iterator it;
    for (it = quads2D.begin(); it != quads2D.end(); it++ ) {
        if((*it)->getId().compare(id) == 0) {
            return *it;
        }
    }
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

vector<Quad2D*> Layer2D::getQuads2D() {
    return quads2D;
}

void Layer2D::draw() {
    if(!enabled)
        return;

    vector<Quad2D*>::iterator it;
    for(it = quads2D.begin(); it != quads2D.end(); it++) {
        (*it)->draw();
    }
}
