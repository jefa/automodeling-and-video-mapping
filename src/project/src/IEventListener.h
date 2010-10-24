#ifndef IEVENTLISTENER_H
#define IEVENTLISTENER_H

#include "EventArg.h"

class IEventListener
{
    virtual void event(EventArg e)=0;
};

#endif // IEVENTLISTENER_H
