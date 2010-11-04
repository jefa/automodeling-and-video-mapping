#ifndef POINTEVENT_H_INCLUDED
#define POINTEVENT_H_INCLUDED

#include "EventArg.h"

class TimedEventArg : public EventArg {
  public:

    string param;
    double _timestamp;
};

#endif
