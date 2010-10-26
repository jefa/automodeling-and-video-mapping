/*
 * ofxMidiIn.h
 *
 *  Created on: 15-sep-2008
 *      Author: arturo
 */

#ifndef OFXMIDIIN_H_
#define OFXMIDIIN_H_

#include <iostream>
#include "RtMidi.h"

class ofxMidiEventManager;
class ofxMidiListener;

void ofxMidiInCallback( double deltatime, std::vector< unsigned char > *message, void *userData );

class ofxMidiIn {
public:
	ofxMidiIn();
	virtual ~ofxMidiIn();

	void listPorts();
	void openPort(unsigned int port=0);
	void newMessage(double deltatime, std::vector< unsigned char > *message);
	unsigned int getPort();
	void setVerbose(bool verbose);

protected:
	RtMidiIn 			midiin;
	unsigned int 		nPorts;
	unsigned int 		port;
	bool				bVerbose;



// events
public:
	void addListener(int id,ofxMidiListener * listener);
	void removeListener(int id,ofxMidiListener * listener);
	void addListener(ofxMidiListener * listener);
	void removeListener(ofxMidiListener * listener);

protected:
	ofxMidiEventManager * eventManager;
};

#endif /* OFXMIDIIN_H_ */
