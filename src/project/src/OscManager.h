#ifndef SYNCHMANAGER_H
#define SYNCHMANAGER_H

#include "IEventListener.h"
#include "ofxOsc.h"
#include <vector>

#define HOST "localhost"
#define PORT 12345

enum SYNCH_MSG_TYPE {
    DISCOVERY, INIT, SYNCH, SHUTDOWN, SETPOINT, ADDQUAD, ANIMATE
};

typedef pair<string, IEventListener*> listenerPair;

struct Node  {
    string address;
    int port;
    bool isActive;
};

using namespace std;

class OscManager
{
    public:
        OscManager(string nodeName, map<string, Node> network, map<string, int > OscPorts = NULL, bool isMaster = true);
        virtual ~OscManager();
        bool SendMessage(string msg, SYNCH_MSG_TYPE msgType, char* destNode = NULL);
        bool SendMessage(ofxOscMessage oscMessage, SYNCH_MSG_TYPE msgType, char* destNode = NULL);
        bool checkForMessages();
        void addListener(IEventListener*, string);

    protected:
        ofxOscSender* getSender(string nodeName);

    private:
        string name;
        bool master;
        map<string,IEventListener*> listeners;

        //ofxOscSender sender;
		ofxOscReceiver	receiver;

        map<string, ofxOscSender*> senders;
        map<string, int > oscPorts;
};

#endif // SYNCHMANAGER_H
