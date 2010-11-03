#include "TimeManager.h"
#include "TimedEventArg.h"

#include "ofAppRunner.h"

static double totalAnimTime;
static double deltaStartTime;       //Tiempo entre que comenzó la aplicación y se hizo init a TimeManager

static map<float, pair<IEventListener*, string> >::iterator it;

static float nextTimeEvent;

map<float, pair<IEventListener*, string> > TimeManager::events;

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
    it = events.begin();
    nextTimeEvent = (*it).first;
    deltaStartTime = ofGetElapsedTimef();
}


void TimeManager::AddTimedEvent(float time, IEventListener *evtLstnr, string param) {
    events.insert(make_pair(time, make_pair(evtLstnr, param)));
}

void TimeManager::Update() {
    totalAnimTime = ofGetElapsedTimef() - deltaStartTime;

    if(totalAnimTime > nextTimeEvent && events.size() > 0) {
        map<float, pair<IEventListener*, string> >::iterator it2 = it;
        ofLog(OF_LOG_VERBOSE, "%f :: llamando a func...", totalAnimTime);
        TimedEventArg *timedEvtArg = new TimedEventArg();
        timedEvtArg->_timestamp = totalAnimTime;
        timedEvtArg->param = (*it).second.second;
        (*it).second.first->event(timedEvtArg);
        ++it;
        events.erase(it2);
        nextTimeEvent = (*it).first;
    }
}
