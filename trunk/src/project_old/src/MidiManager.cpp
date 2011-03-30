#include "MidiManager.h"
#include "ofUtils.h"

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


	EventArg *evtArg = new EventArg();

    //evtArg->type = "MIDI";
	evtArg->args.addIntArg(_value);
	evtArg->args.addIntArg(_id);
	evtArg->args.addIntArg(_port);
	evtArg->args.addFloatArg(_timestamp);

    map<string, IEventListener*>::iterator iter = listeners.begin();
    while (iter != listeners.end() ) {
        iter->second->event(evtArg);
        iter++;
    }

}
