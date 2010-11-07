#ifndef EVENTARGS_H_INCLUDED
#define EVENTARGS_H_INCLUDED

#include "ofxOsc.h"
#include <string>

using namespace std;

class EventArg{
    public:
        string type;
        ofxOscMessage args;
};

#endif // EVENTARGS_H_INCLUDED
