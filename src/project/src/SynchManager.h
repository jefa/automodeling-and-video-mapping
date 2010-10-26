#ifndef SYNCHMANAGER_H
#define SYNCHMANAGER_H

#include "IEventListener.h"
#include "ofxOsc.h"
#include <vector>

#define HOST "localhost"
#define PORT 12345

enum SYNCH_MSG_TYPE {
    DISCOVERY, INIT, SYNCH, SHUTDOWN, SETPOINT, ADDQUAD
};

typedef pair<string, IEventListener*> listenerPair;

using namespace std;

class SynchManager
{
    public:
        SynchManager();
        SynchManager(bool isMaster = true);
        virtual ~SynchManager();
        bool SendMessage(string msg, SYNCH_MSG_TYPE msgType);
        bool SendMessage(ofxOscMessage oscMessage, SYNCH_MSG_TYPE msgType);
        bool checkForMessages();
        void addListener(IEventListener*, string);

    protected:

    private:
        ofxOscSender sender;
		ofxOscReceiver	receiver;
        bool master;
        map<string,IEventListener*> listeners;
        //vector<IEventListener*> listeners;

};

#endif // SYNCHMANAGER_H
