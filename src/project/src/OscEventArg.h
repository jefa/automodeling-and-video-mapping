#ifndef IACTIONEVENT_H_INCLUDED
#define IACTIONEVENT_H_INCLUDED

#include "ofxOsc.h"

class OscEventArg : public EventArg {
  public:
    ofxOscMessage oscMessage;
};

#endif
