#ifndef TIMEDEVENT_H_INCLUDED
#define TIMEDEVENT_H_INCLUDED

#include "EventArg.h"
#include <string>
using namespace std;

class TimedEventArg : public EventArg {
  public:
    TimedEventArg() {
        this->source = "TimedEventArg";
    }
    double _timestamp;
    string opName;
    string param1;
    string param2;
};

#endif
