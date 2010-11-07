#include "TimeManager.h"

#include "ofAppRunner.h"
#include "OscManager.h"

static double totalAnimTime;
static double deltaStartTime;       //Tiempo entre que comenzó la aplicación y se hizo init a TimeManager

map<float, pair<string, EventArg*> > TimeManager::events;
static map<float, pair<string, EventArg*> >::iterator it;

static float nextTimeEvent;
bool moreEvents = true;

TimeManager::TimeManager()
{
    //ctor
}

TimeManager::~TimeManager()
{
    //dtor
}

void TimeManager::Init() {
    totalAnimTime = 0;
    if(events.size() > 0) {
        it = events.begin();
        nextTimeEvent = (*it).first;
    }
    else {
        moreEvents = false;
    }

    deltaStartTime = ofGetElapsedTimef();
}

void TimeManager::ScheduleEvent(float time, string destination, EventArg *eventArg) {
    float time_fixed = time;

    while(events.count(time_fixed) > 0) {
        time_fixed += 0.001f;
    }
    events.insert(make_pair(time_fixed, make_pair(destination, eventArg)));
}

void TimeManager::Update() {
    totalAnimTime = ofGetElapsedTimef() - deltaStartTime;

    if(moreEvents && events.size() > 0 && totalAnimTime > nextTimeEvent) {
        ofLog(OF_LOG_VERBOSE, "%f :: llamando a func...", totalAnimTime);

        /*EventArg *timedEvtArg = (*it).second.second;
        timedEvtArg->_timestamp = totalAnimTime;
        (*it).second.first->event(timedEvtArg);
        */ //ACA ENVIAR EVENTO POR OSC A DESTINATARIOS CORRECTOS
        OscManager::SendMessage(it->second.second->args, it->second.first);

        ++it;

        if(it == events.end()) {
            moreEvents = false;
        }
        else {
            nextTimeEvent = it->first;
        }
    }/* else {
        ofLog(OF_LOG_NOTICE, "TimeManager:: No timed events to process in update.");
    }*/
}
