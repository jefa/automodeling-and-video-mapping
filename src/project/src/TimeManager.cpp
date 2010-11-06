#include "TimeManager.h"

#include "ofAppRunner.h"

static double totalAnimTime;
static double deltaStartTime;       //Tiempo entre que comenzó la aplicación y se hizo init a TimeManager

static map<float, pair<IEventListener*, TimedEventArg*> >::iterator it;

static float nextTimeEvent;

map<float, pair<IEventListener*, TimedEventArg*> > TimeManager::events;

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

void TimeManager::AddTimedEvent(float time, IEventListener *evtLstnr, string opName, string param1, string param2) {
    TimedEventArg *timedEvtArg = new TimedEventArg();
    timedEvtArg->opName = opName;
    timedEvtArg->param1 = param1;
    timedEvtArg->param2 = param2;

    float time_fixed = time;

    while(events.count(time_fixed) > 0) {
        time_fixed += 0.001f;
    }
    events.insert(make_pair(time_fixed, make_pair(evtLstnr, timedEvtArg)));
}

void TimeManager::Update() {
    totalAnimTime = ofGetElapsedTimef() - deltaStartTime;

    if(moreEvents && events.size() > 0 && totalAnimTime > nextTimeEvent) {
        ofLog(OF_LOG_VERBOSE, "%f :: llamando a func...", totalAnimTime);
        TimedEventArg *timedEvtArg = (*it).second.second;
        timedEvtArg->_timestamp = totalAnimTime;
        (*it).second.first->event(timedEvtArg);
        ++it;
        if(it == events.end()) {
            moreEvents = false;
        }
        else {
            nextTimeEvent = (*it).first;
        }
    }/* else {
        ofLog(OF_LOG_NOTICE, "TimeManager:: No timed events to process in update.");
    }*/
}
