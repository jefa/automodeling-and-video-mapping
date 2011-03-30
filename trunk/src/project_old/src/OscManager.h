#ifndef SYNCHMANAGER_H
#define SYNCHMANAGER_H

#include "IEventListener.h"
#include "ofxOsc.h"
#include <vector>
using namespace std;

enum SYNCH_MSG_TYPE {
    SETPOINT, ADDQUAD, ANIMATE
};

struct Node  {
    string address;
    int port;
    bool isActive;
};

class OscManager
{
    public:
        OscManager();
        virtual ~OscManager();
        static void Init(string nodeName, map<string, Node> network, map<string, int> OscPorts, bool isMaster = true);
        static void SendMessage(ofxOscMessage oscMessage, string destNode = "");
        static void Update();
        static void AddListener(IEventListener*, string);

    protected:
        static ofxOscSender* getSender(string nodeName);

    private:
        static string name;
        static bool master;
        static map<string,IEventListener*> listeners;

		static ofxOscReceiver	receiver;

        static map<string, ofxOscSender*> senders;
        static map<string, int > oscPorts;
};

#endif // SYNCHMANAGER_H
