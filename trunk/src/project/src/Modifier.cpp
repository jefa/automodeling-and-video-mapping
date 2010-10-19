#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Modifier.h"
#include "Object3D.h"

Modifier::Modifier()
{
}

Modifier::Modifier(Object3D *objRef)
{
    this->objRef = objRef;
}

Modifier::~Modifier()
{
    this->objRef = NULL;
}

void Modifier::getGizmo()
{
	throw "Not yet implemented";
}

