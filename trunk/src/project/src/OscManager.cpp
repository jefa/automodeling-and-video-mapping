#include "OscManager.h"

string OscManager::name;
bool OscManager::master;
map<string,IEventListener*> OscManager::listeners;
ofxOscReceiver OscManager::receiver;
map<string, ofxOscSender*> OscManager::senders;
map<string, int > OscManager::oscPorts;

OscManager::OscManager() {
}

void OscManager::Init(string nodeName, map<string, Node> network, map<string, int> OscPorts, bool isMaster)
{
    OscManager::name = nodeName;
    OscManager::oscPorts = OscPorts;
    OscManager::master = isMaster;

    if (isMaster)
    {
        ofLog(OF_LOG_VERBOSE, "OscManager:: Configuring as Master");

        map<string, Node>::iterator iter = network.begin();
        while (iter != network.end() )
        {
            string nName = iter->first;
            Node n = iter->second;
            //ofLog(OF_LOG_VERBOSE, "OscManager:: Detected node %s:%d", n.address, n.port);

            ofxOscSender *sender = new ofxOscSender();
            sender->setup(n.address, n.port);
            senders.insert (pair<string, ofxOscSender*>(nName, sender));

            iter++;
        }
        //sender.setup( HOST, PORT );
    } else {

        //buscar en OSCPorts el puerto a escuchar

        map<string, int>::iterator p = OscPorts.find("osc");
        if(p != OscPorts.end()){
            int receivePort = p->second;
            ofLog(OF_LOG_VERBOSE, "OscManager:: Configuring as Slave (receiver). Port=%d",receivePort);
            receiver.setup( receivePort );
        } else
            ofLog(OF_LOG_WARNING, "OscManager:: Node declared as SLAVE but no OSCPORT defined for '"+name+"'");

        //receiver.setup( PORT );
    }
    ofLog(OF_LOG_VERBOSE, "OscManager:: Configured!");

}

OscManager::~OscManager()
{
     ofLog(OF_LOG_VERBOSE, "OscManager:: Destroying...");
}

void OscManager::AddListener(IEventListener *listener, string evtKey)
{
    listeners.insert(make_pair(evtKey, listener));
}

void OscManager::SendMessage(ofxOscMessage oscMessage, string destNode)
{
    //ofLog(OF_LOG_VERBOSE, "OscManager:: Sending message: type=%s", oscMessage.getAddress().c_str());

    if (!destNode.empty()){
        getSender(destNode.c_str())->sendMessage( oscMessage );
    }
    else {
        map<string, ofxOscSender*>::iterator iter = senders.begin();
        while (iter != senders.end()) {
            iter->second->sendMessage( oscMessage );
            iter++;
        }
    }
}

void OscManager::Update()
{
    string msg_string;

    //ofLog(OF_LOG_VERBOSE, "OscManager: Checking for messages...\n");
    while( receiver.hasWaitingMessages() )
    {
        ofxOscMessage m;
        receiver.getNextMessage( &m );
        EventArg *evtArg = new EventArg();
        evtArg->type = "OSC";

        if ( m.getAddress() == "/synch/setpoint" )
        {
            evtArg->args.setAddress("/synch/setpoint");
            evtArg->args.addIntArg(m.getArgAsInt32(0));
            evtArg->args.addIntArg(m.getArgAsInt32(1));
            evtArg->args.addIntArg(m.getArgAsInt32(2));
            evtArg->args.addIntArg(m.getArgAsInt32(3));
            //ofLog(OF_LOG_VERBOSE, "OscManager: SynchEvent/SetPoint received = [%d,%d,%f,%f]",((DrawEventArg*)evtArg)->_shapeId,
            //      ((DrawEventArg*)evtArg)->_vertexId, ((DrawEventArg*)evtArg)->_x, ((DrawEventArg*)evtArg)->_y);
        }
        else if ( m.getAddress() == "/synch/addquad" )
        {
            evtArg->args.setAddress("/synch/addquad");
            evtArg->args.addStringArg(m.getArgAsString(0));
            ofLog(OF_LOG_VERBOSE, "OscManager: SynchEvent/AddQuad received for "+m.getArgAsString(0));
        }
        else if ( m.getAddress() == "/synch/removequad" )
        {
            evtArg->args.setAddress("/synch/removequad");
            evtArg->args.addStringArg(m.getArgAsString(0));
            ofLog(OF_LOG_VERBOSE, "OscManager: SynchEvent/RemoveQuad received for "+m.getArgAsString(0));
        }
        else
        {
            msg_string = m.getAddress();
            msg_string += ": ";
            for ( int i=0; i<m.getNumArgs(); i++ )
            {
                msg_string += m.getArgTypeName( i );
                msg_string += ":";
                if( m.getArgType( i ) == OFXOSC_TYPE_INT32 )
                    msg_string += ofToString( m.getArgAsInt32( i ) );
                else if( m.getArgType( i ) == OFXOSC_TYPE_FLOAT )
                    msg_string += ofToString( m.getArgAsFloat( i ) );
                else if( m.getArgType( i ) == OFXOSC_TYPE_STRING )
                    msg_string += m.getArgAsString( i );
                else
                    msg_string += "unknown";
            }
            ofLog(OF_LOG_VERBOSE, "OscManager: Unrecognized message: %s\n", msg_string);
        }


        /*map<string, IEventListener*>::iterator l = listeners.find(s);
        if(l != listeners.end())
            cout << "Numero telefonico de : " << s << " = " << l->second << endl;
        else
            cout << s << " no está en listeners.\n";
        */

        map<string, IEventListener*>::iterator iter = listeners.begin();
        while (iter != listeners.end() )
        {
            iter->second->event(evtArg);
            iter++;
        }
    }
}

ofxOscSender* OscManager::getSender(string nodeName){
    map<string, ofxOscSender*>::iterator s = senders.find(nodeName);
    if(s != senders.end())
        return s->second;
    else
        ofLog(OF_LOG_WARNING, "OscManager:: In getSender cannot find node for name '"+nodeName+"'");
    return NULL;
}


