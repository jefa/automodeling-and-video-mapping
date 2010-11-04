#ifndef TIMEDEVENT_H_INCLUDED
#define TIMEDEVENT_H_INCLUDED

#include "EventArg.h"

class TimedEventArg : public EventArg {
  public:
    TimedEventArg() {
        this->source = "TimedEventArg";
    }
    double _timestamp;
    string param;
};

#endif
