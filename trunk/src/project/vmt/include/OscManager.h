#ifndef OSCMANAGER_H
#define OSCMANAGER_H

#include "ofxOsc.h"
#include <vector>

using namespace std;

struct Node  {
    string address;
    int port;
    bool isActive;
    string cameraId;
};

class OscManager
{
    public:
        OscManager();
        ~OscManager();
        void Init(map<string, Node> network);
        void SendMessage(ofxOscMessage oscMessage, string destNode = "");
        void checkForMessages();

    protected:
        ofxOscSender* getSender(string nodeName);

    private:
		//ofxOscReceiver receiver;
        map<string, ofxOscSender*> senders;
};

#endif
