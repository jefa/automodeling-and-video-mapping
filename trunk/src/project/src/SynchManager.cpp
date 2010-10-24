#include "SynchManager.h"

SynchManager::SynchManager(bool isMaster)
{
    this->master = isMaster;
    if (isMaster)
    {
        ofLog(OF_LOG_VERBOSE, "SynchManager:: Configuring as master. Port=%s Host=%s",PORT, HOST);
        sender.setup( HOST, PORT );
    } else
    {
        ofLog(OF_LOG_VERBOSE, "SynchManager:: Configuring as listener. Port=%s",PORT, HOST);
        receiver.setup( PORT );
    }
}

SynchManager::~SynchManager()
{
     ofLog(OF_LOG_VERBOSE, "SynchManager:: Destroying...");
}

void SynchManager::SendMessage(string msg)
{
    ofLog(OF_LOG_VERBOSE, "SynchManager:: Sending message=%s",msg);
	ofxOscMessage m;
	m.setAddress( /*SYNCH_MSG_TYPE.SYNCH*/ "/osc/synchevent" );
	m.addStringArg( msg );
	sender.sendMessage( m );
}

bool SynchManager::checkForMessages()
{
    string msg_string;

    while( receiver.hasWaitingMessages() )
    {
        ofxOscMessage m;
        receiver.getNextMessage( &m );

        if ( m.getAddress() == "/osc/synchevent" )
        {
            msg_string = m.getArgAsString( 0 );
            ofLog(OF_LOG_VERBOSE, "OscEvent: SynchEvent received = %s",msg_string);
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
            ofLog(OF_LOG_VERBOSE, "OscEvent: Unrecognized message: %s", msg_string);
        }

        OscEventArg evtArg = OscEventArg();
        evtArg.oscMessage = m;
        //event((EventArg)evtArg);
    }
}

void SynchManager::event(EventArg e)
{
    ofLog(OF_LOG_VERBOSE, "En new OSCSTRING!!");
}
