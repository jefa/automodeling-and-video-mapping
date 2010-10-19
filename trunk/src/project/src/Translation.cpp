#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Translation.h"

float Translation::get(string aParam) {
    if (aParam.compare("x") == 0)
    {
        return this->objRef->getPosX();

    } else if (aParam.compare("y") == 0)
    {
        return this->objRef->getPosY();

    } else if (aParam.compare("z") == 0)
    {
        return this->objRef->getPosZ();
    }
    return 0;
}

void Translation::set(string aParam, float aValue) {
    if (aParam.compare("x") == 0)
    {
        this->objRef->setPosX(aValue);

    } else if (aParam.compare("y") == 0)
    {
        this->objRef->setPosY(aValue);

    } else if (aParam.compare("z") == 0)
    {
        this->objRef->setPosZ(aValue);
    }
}

