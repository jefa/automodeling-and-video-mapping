#ifndef SYNCHMANAGER_H
#define SYNCHMANAGER_H

#include "IEventListener.h"
#include "OscEventArg.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

enum SYNCH_MSG_TYPE {DISCOVERY, INIT, SYNCH, SHUTDOWN};

class SynchManager : public IEventListener
{
    public:
        SynchManager();
        SynchManager(bool isMaster = true);
        virtual ~SynchManager();
        void SendMessage(string msg);
        bool checkForMessages();
        //void newOscString();

        void event(EventArg e);

    protected:

    private:
        ofxOscSender sender;
		ofxOscReceiver	receiver;
        bool master;
};

#endif // SYNCHMANAGER_H
