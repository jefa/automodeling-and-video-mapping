#ifndef OSCMANAGER_H
#define OSCMANAGER_H

#include "ISerializable.h"

#include "ofxOsc.h"
#include <vector>

using namespace std;

class Node  {

public:
    string id;
    string address;
    int port;
    bool isActive;
    string cameraId;
};

class OscManager : public ISerializable
{
    public:
        OscManager();
        ~OscManager();
        void Init(map<string, Node*> network);
        void SendMessage(ofxOscMessage oscMessage, string destNode);
        void SendMessageAll(ofxOscMessage oscMessage);
        void checkForMessages();

        virtual SerializedNode* Serialize();
    protected:
        ofxOscSender* getSender(string nodeName);

    private:
		//ofxOscReceiver receiver;
        map<string, ofxOscSender*> senders;

        map<string, Node> network_copy;
};

#endif
