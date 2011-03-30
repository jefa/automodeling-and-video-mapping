/*
 * ofxMidiEvents.h
 *
 *  Created on: 15-sep-2008
 *      Author: art
 */

#ifndef OFXMIDIEVENTS_H_
#define OFXMIDIEVENTS_H_

#include "Poco/FIFOEvent.h"
#include "Poco/Delegate.h"
#include "ofTypes.h"
#include "ofxMidiIn.h"
#include <map>
#include "ofEvents.h"


class ofxMidiEventArgs: public ofEventArgs{
public:
	int 	id;
	int 	value;
	double 	timestamp;
};

class ofxMidiListener {
public:
	ofxMidiListener(){}
	virtual ~ofxMidiListener(){}

protected:

	virtual void newMessage(int port, int id, int value, double timestamp){};

public:

	void newMessage(const void* sender, ofxMidiEventArgs& eventArgs){
		ofxMidiEventArgs& midiArgs = (ofxMidiEventArgs&)eventArgs;
		newMessage( ((ofxMidiIn*)sender)->getPort(), midiArgs.id, midiArgs.value, midiArgs.timestamp);
	}

};


typedef Poco::FIFOEvent<ofxMidiEventArgs> midiEvent;

class ofxMidiEventManager {

public:
	ofxMidiEventManager(ofxMidiIn * sender){
		this->sender=sender;

	}
	virtual ~ofxMidiEventManager(){}

	void addListener(ofxMidiListener* listener){
		generalEvent += Poco::Delegate<ofxMidiListener, ofxMidiEventArgs>(listener, &ofxMidiListener::newMessage);
	}
	void removeListener(ofxMidiListener* listener){
		generalEvent -= Poco::Delegate<ofxMidiListener, ofxMidiEventArgs>(listener, &ofxMidiListener::newMessage);
	}
	void addListener(int id,ofxMidiListener* listener){
		midiEvent * event;
		map<int,midiEvent*>::iterator iter = events.find(id);
		if(iter == events.end()){
			event = new midiEvent();
			events.insert(make_pair(id,event));
		}else{
			event=iter->second;
		}
		*event += Poco::Delegate<ofxMidiListener, ofxMidiEventArgs>(listener, &ofxMidiListener::newMessage);
	}

	void removeListener(int id,ofxMidiListener* listener){
		map<int,midiEvent*>::iterator iter = events.find(id);
		if(iter != events.end()){
			midiEvent * event = iter->second;
			*event -= Poco::Delegate<ofxMidiListener, ofxMidiEventArgs>(listener, &ofxMidiListener::newMessage);
		}
	}

	void notify(ofxMidiEventArgs& eventArgs){
		map<int,midiEvent*>::iterator iter = events.find(eventArgs.id);
		if(iter != events.end()){
			midiEvent * event = iter->second;
			event->notify(sender, eventArgs);
		}
		generalEvent.notify(sender,eventArgs);
	}

private:
	ofxMidiIn * 		sender;
	map<int,midiEvent*> events;
	midiEvent 			generalEvent;

};

#endif /* OFXMIDIEVENTS_H_ */
