#include "OscManager.h"
#include "DrawEventArg.h"
#include "AnimEventArg.h"

OscManager::OscManager(bool isMaster)
{
    this->master = isMaster;
    if (isMaster)
    {
        ofLog(OF_LOG_VERBOSE, "OscManager:: Configuring as Master (sender). Port=%d Host=%s",PORT, HOST);
        sender.setup( HOST, PORT );
    } else
    {
        ofLog(OF_LOG_VERBOSE, "OscManager:: Configuring as Slave (receiver). Port=%d",PORT);
        receiver.setup( PORT );
    }
}

OscManager::~OscManager()
{
     ofLog(OF_LOG_VERBOSE, "OscManager:: Destroying...");
}

void OscManager::addListener(IEventListener *listener, string evtKey)
{
    listeners.insert( listenerPair(evtKey, listener) );

    /*map<string, IEventListener*>::iterator iter = listeners.begin();
    while (iter != listeners.end() )
    {
        ofLog(OF_LOG_VERBOSE, "====== Listener %d\n", iter);
        iter++;
    }*/

    /*string s = "Ruben";
    map<string, string>::iterator p = directorio.find(s);
    if(p != directorio.end())
        cout << "Numero telefonico de : " << s << " = " << p->second << endl;
    else
        cout << s << " no está en el directorio.\n";
    */

}

bool OscManager::SendMessage(string msg, SYNCH_MSG_TYPE msgType)
{
    if (msgType == SETPOINT)
    {
        ofLog(OF_LOG_VERBOSE, "OscManager:: Sending message=%s\n",msg);
        ofxOscMessage m;
        m.setAddress( /*SYNCH_MSG_TYPE.SYNCH*/ "/synch/setpoint" );
        m.addStringArg( msg );
        sender.sendMessage( m );
    } else if (msgType == ANIMATE)
    {
        ofLog(OF_LOG_VERBOSE, "OscManager:: Sending message=%s\n",msg);
        ofxOscMessage m;
        m.setAddress( /*SYNCH_MSG_TYPE.SYNCH*/ "/synch/animationloop" );
        m.addStringArg( msg );
        sender.sendMessage( m );
    }
    return true;
}

bool OscManager::SendMessage(ofxOscMessage oscMessage, SYNCH_MSG_TYPE msgType)
{
    ofLog(OF_LOG_VERBOSE, "OscManager:: Sending message: type=%d",msgType);
    if (msgType == SETPOINT)
    {
        oscMessage.setAddress( /*SYNCH_MSG_TYPE.SYNCH*/ "/synch/setpoint" );
    } else if (msgType == ADDQUAD)
    {
        oscMessage.setAddress( /*SYNCH_MSG_TYPE.SYNCH*/ "/synch/addquad" );
    }
    sender.sendMessage( oscMessage );
    return true;
}

bool OscManager::checkForMessages()
{
    string msg_string;

    //ofLog(OF_LOG_VERBOSE, "OscManager: Checking for messages...\n");
    while( receiver.hasWaitingMessages() )
    {
        ofxOscMessage m;
        receiver.getNextMessage( &m );
        EventArg *evtArg;

        if ( m.getAddress() == "/synch/setpoint" )
        {
            evtArg = new DrawEventArg();
            ((DrawEventArg*)evtArg)->_shapeId = m.getArgAsInt32(0);
            ((DrawEventArg*)evtArg)->_vertexId = m.getArgAsInt32(1);
            ((DrawEventArg*)evtArg)->_x = m.getArgAsInt32(2);
            ((DrawEventArg*)evtArg)->_y = m.getArgAsInt32(3);
            ((DrawEventArg*)evtArg)->_evtType = 0;
            ofLog(OF_LOG_VERBOSE, "OscManager: SynchEvent/SetPoint received = [%d,%d,%f,%f]",((DrawEventArg*)evtArg)->_shapeId,
                  ((DrawEventArg*)evtArg)->_vertexId, ((DrawEventArg*)evtArg)->_x, ((DrawEventArg*)evtArg)->_y);
        }
        else if ( m.getAddress() == "/anim/animate" )
        {
            string anim_id = m.getArgAsString(0);
            ofLog(OF_LOG_VERBOSE, "OscManager: Anim/Animate received. Id = %s\n",anim_id);
            evtArg = new AnimEventArg();
            ((AnimEventArg*)evtArg)->isActivate = true;
            ((AnimEventArg*)evtArg)->id = anim_id;
        }
        else if ( m.getAddress() == "/synch/addquad" )
        {
            evtArg = new DrawEventArg();
            ((DrawEventArg*)evtArg)->_shapeId = m.getArgAsInt32(0);
            ((DrawEventArg*)evtArg)->source = m.getArgAsString(1);
            ((DrawEventArg*)evtArg)->_evtType = 1;
            ofLog(OF_LOG_VERBOSE, "OscManager: SynchEvent/AddQuad received");
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
            //ofLog(OF_LOG_VERBOSE, "====== Listener \n"/*, iter->first*/);
            iter->second->event(evtArg);
            iter++;
        }
    }
}
