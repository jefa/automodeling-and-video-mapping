#include "MidiManager.h"
#include "ofUtils.h"

MidiManager::MidiManager()
{


}

MidiManager::~MidiManager()
{
     ofLog(OF_LOG_VERBOSE, "MidiManager:: Destroying...");
}

void MidiManager::addListener(ofxMidiListener *listener, string evtKey)
{


     midiIn.listPorts();
     midiIn.openPort(0);
     midiIn.addListener(listener);

	 // to register only to one controller pass the id as first argument
     // midiIn.addListener(84,this);

     // to debug
     //midiIn.setVerbose(true);

}

//midiIn events
void MidiManager::newMessage(int _port, int _id, int _value, double _timestamp){
	value 		= _value;
	id 			= _id;
	port 		= _port;
	timestamp 	= _timestamp;
	cout<<"MidiManager::newMessage";
}

