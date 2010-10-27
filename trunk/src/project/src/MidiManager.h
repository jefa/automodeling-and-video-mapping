#ifndef MIDIMANAGER_H
#define MIDIMANAGER_H

#include "IEventListener.h"
#include "ofxMidiIn.h"


using namespace std;

class MidiManager
{
    public:
        MidiManager();
        virtual ~MidiManager();
        void addListener(ofxMidiListener*, string);

        int port;
		int id;
		int value;
		double timestamp;
		char msg[255];
        void newMessage(int port, int id, int value, double timestamp);

    protected:

    private:
        ofxMidiIn	midiIn;
       // map<string,IEventListener*> listeners;

};

#endif // MIDIMANAGER_H
