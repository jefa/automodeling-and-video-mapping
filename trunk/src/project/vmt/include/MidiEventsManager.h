#ifndef MIDIEVENTSMANAGER_H
#define MIDIEVENTSMANAGER_H

#include "ISerializable.h"

#include <string>
#include <map>
#include "..\addons\ofxMidiIn\src\ofxMidiIn.h"
#include "..\addons\ofxMidiIn\events\ofxMidiEvents.h"

using namespace std;

class MidiEventsManager : public ISerializable, ofxMidiListener{

    public:
        MidiEventsManager();
        virtual ~MidiEventsManager();

        void addMidiEvent(ofxMidiEventArgs*	msg, string effectId);
        bool hasMidiEvent(ofxMidiEventArgs*	msg);
        string getEffectId(ofxMidiEventArgs*	msg);
        map<ofxMidiEventArgs*, string> getMidiEvents();

        virtual SerializedNode* Serialize();

    protected:
        //midiIn events
        void newMessage(int port, int id, int value, double timestamp);
		void newMidiMessage(ofxMidiEventArgs& eventArgs);

    private:
        ofxMidiIn	midiIn;
        map<ofxMidiEventArgs*, string> events;
};

#endif // MIDIEVENTSMANAGER_H
