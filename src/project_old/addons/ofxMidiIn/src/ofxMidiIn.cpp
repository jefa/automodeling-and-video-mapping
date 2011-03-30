/*
 * ofxMidiIn.cpp
 *
 *  Created on: 15-sep-2008
 *      Author: arturo
 */

#include "ofxMidiIn.h"
#include "ofxMidiEvents.h"

void ofxMidiInCallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
	((ofxMidiIn*)userData)->newMessage(deltatime,message);

}

ofxMidiIn::ofxMidiIn() {
	eventManager = new ofxMidiEventManager(this);
	// Check available ports.
	nPorts = midiin.getPortCount();
}

ofxMidiIn::~ofxMidiIn() {
}

void ofxMidiIn::listPorts(){
	printf( " %i ports available \n", nPorts );
	for(unsigned int i=0; i<nPorts; i++){
		printf("%i: %s\n",i,midiin.getPortName(i).c_str());
	}
}

void ofxMidiIn::openPort(unsigned int _port){
	if ( nPorts == 0 ) {
		printf( "No ports available!\n" );
		return;
	}
	if ( _port+1 > nPorts ){
		printf("The selected port is not available\n");
		return;
	}

	port = _port;
	midiin.openPort( port );
	// Set our callback function.  This should be done immediately after
	// opening the port to avoid having incoming messages written to the
	// queue.
	midiin.setCallback( &ofxMidiInCallback, this );

	// Don't ignore sysex, timing, or active sensing messages.
	midiin.ignoreTypes( false, false, false );
}


void ofxMidiIn::newMessage(double deltatime, std::vector< unsigned char > *message){

	unsigned int nBytes = message->size();
	if(bVerbose){
		std::cout << "num bytes: "<<nBytes;
		for ( unsigned int i=0; i<nBytes; i++ )
			std::cout << " Byte " << i << " = " << (int)message->at(i) << ", ";
		if ( nBytes > 0 )
			std::cout << "stamp = " << deltatime << '\n';
	}

	if(nBytes == 3){
		ofxMidiEventArgs eventArgs;
		eventArgs.id=(int)message->at(1);
		eventArgs.value=(int)message->at(2);
		eventArgs.timestamp=deltatime;
		eventManager->notify(eventArgs);
	}

}
void ofxMidiIn::setVerbose(bool verbose){
	bVerbose=verbose;
}

unsigned int ofxMidiIn::getPort(){
	return port;
}

void ofxMidiIn::addListener(int id, ofxMidiListener * listener){
	eventManager->addListener(id,listener);
}

void ofxMidiIn::removeListener(int id, ofxMidiListener * listener){
	eventManager->removeListener(id,listener);
}

void ofxMidiIn::addListener(ofxMidiListener * listener){
	eventManager->addListener(listener);
}

void ofxMidiIn::removeListener(ofxMidiListener * listener){
	eventManager->removeListener(listener);
}
