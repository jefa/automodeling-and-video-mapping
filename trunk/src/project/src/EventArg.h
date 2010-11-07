#ifndef EVENTARGS_H_INCLUDED
#define EVENTARGS_H_INCLUDED

#include "ofxOsc.h"
#include <string>

using namespace std;

class EventArg{
    public:
        string type;
        ofxOscMessage args;

        EventArg() {}

        EventArg(string address, string param1, string param2, string param3, string param4, string param5) {
            args.setAddress(address);
            args.addStringArg(param1);
            args.addStringArg(param2);
            args.addStringArg(param2);
            args.addStringArg(param3);
            args.addStringArg(param4);
            args.addStringArg(param5);
        }

        EventArg(string address, string param1, string param2) {
            args.setAddress(address);
            args.addStringArg(param1);
            args.addStringArg(param2);
        }

        EventArg(string address, string param1) {
            args.setAddress(address);
            args.addStringArg(param1);
        }
};

#endif // EVENTARGS_H_INCLUDED
