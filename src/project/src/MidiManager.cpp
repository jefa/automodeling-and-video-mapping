#include "MidiManager.h"
#include "ofUtils.h"
#include "MidiEventArg.h"


MidiManager::MidiManager()
{
     midiIn.listPorts();
     midiIn.openPort(0);

     midiIn.addListener(this);

	 // to register only to one controller pass the id as first argument
     // midiIn.addListener(84,this);

     // to debug
     midiIn.setVerbose(true);
}

MidiManager::~MidiManager()
{
     ofLog(OF_LOG_VERBOSE, "MidiManager:: Destroying...");
}

void MidiManager::addListener(IEventListener *listener, string evtKey)
{
    listeners.insert( listenerPair(evtKey, listener) );
}

//midiIn events
void MidiManager::newMessage(int _port, int _id, int _value, double _timestamp){
	value 		= _value;
	id 			= _id;
	port 		= _port;
	timestamp 	= _timestamp;
	cout<<"MidiManager::newMessage  Bulid Message ";


	EventArg *evtArg;

	// armar el mensaje a mandar  de ieventlistener
	evtArg = new MidiEventArg();

	((MidiEventArg*)evtArg)->_value = _value;
	((MidiEventArg*)evtArg)->_id = _id;
	((MidiEventArg*)evtArg)->_port = _port;
	((MidiEventArg*)evtArg)->_timestamp = _timestamp;


    map<string, IEventListener*>::iterator iter = listeners.begin();
    while (iter != listeners.end() ) {
        iter->second->event(evtArg);
        iter++;
    }

}
