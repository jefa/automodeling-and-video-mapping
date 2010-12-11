#include "TimeManager.h"

#include "ofAppRunner.h"
#include "OscManager.h"

static double totalAnimTime;
static double deltaStartTime;       //Tiempo entre que comenzó la aplicación y se hizo init a TimeManager

map<float, pair<string, EventArg*> > TimeManager::events;
static map<float, pair<string, EventArg*> >::iterator it;

static float nextTimeEvent;
static float timeOffset;
bool moreEvents = true;
bool noUpdate = false;

IEventListener *evtlstnr;

TimeManager::TimeManager()
{
    //ctor
}

TimeManager::~TimeManager()
{
    //dtor
}

void TimeManager::Init(IEventListener *e) {

    InitializeInternal();

    evtlstnr = e;
    EventArg *evtArgs = new EventArg("/internal/playaudio", "");
    e->event(evtArgs);
}

void TimeManager::InitializeInternal() {
    totalAnimTime = 0;
    timeOffset = 0;

    if(events.size() > 0) {
        it = events.begin();
        //ofLog(OF_LOG_VERBOSE, "TimeManager: SETEANDO NEXTEVENT1111");
        nextTimeEvent = it->first;
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

    if (noUpdate)
        return;

    totalAnimTime = ofGetElapsedTimef() - deltaStartTime + timeOffset;

    //ofLog(OF_LOG_VERBOSE, "========= TOTALANUMTIME=%f, NEXTEVENT=%f", totalAnimTime, nextTimeEvent);


    if(moreEvents && events.size() > 0 && totalAnimTime > nextTimeEvent) {
        ofLog(OF_LOG_VERBOSE, "%f :: llamando a func...", totalAnimTime);

        string destination = it->second.first.c_str();
        ofxOscMessage msg = it->second.second->args;

        OscManager::SendMessage(msg, destination);

        evtlstnr->event(it->second.second);//Esto es para mostrar los eventos en consola tambien.

        ++it;

        if(it == events.end()) {
            moreEvents = false;
        }
        else {
            //ofLog(OF_LOG_VERBOSE, "TimeManager: SETEANDO NEXTEVENT2222");
            nextTimeEvent = it->first;
        }
    }
}

void TimeManager::SetOffset(float offset) {
    timeOffset = offset;
    totalAnimTime = ofGetElapsedTimef() - deltaStartTime;

    if(moreEvents && events.size() > 0) {
        //ofLog(OF_LOG_VERBOSE, "TimeManager: tiempo considerado %f", (totalAnimTime + timeOffset));
        //ofLog(OF_LOG_VERBOSE, "TimeManager: Next time event %f", nextTimeEvent);
        while (( totalAnimTime + timeOffset > nextTimeEvent) && moreEvents) {
            //ofLog(OF_LOG_VERBOSE, "TimeManager: moviendo...");
            ++it;
            if(it == events.end()) {
                moreEvents = false;
            } else {
                //ofLog(OF_LOG_VERBOSE, "TimeManager: SETEANDO NEXTEVENT3333");
                nextTimeEvent = it->first;
            }
        }
    }
}

void TimeManager::SetTime(float to_time) {

    noUpdate = true;

    if (to_time > totalAnimTime){ //moving forward
        ofLog(OF_LOG_VERBOSE, "TimeManager: Moviendo para adelante");

    } else if (to_time < totalAnimTime){ //moving backwards
        ofLog(OF_LOG_VERBOSE, "TimeManager: Moviendo para atras");

        //reinit events
        InitializeInternal();
    }

    SetOffset(to_time);

    noUpdate = false;
}
