#ifndef POINTEVENT_H_INCLUDED
#define POINTEVENT_H_INCLUDED

#include "EventArg.h"

class MidiEventArg : public EventArg {
  public:
    int _port;
    int _id;
    int _value;
    double _timestamp;
};

#endif
