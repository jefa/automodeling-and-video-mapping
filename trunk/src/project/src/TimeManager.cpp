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
    totalAnimTime = 0;
    timeOffset = 0;
    evtlstnr = e;
    if(events.size() > 0) {
        it = events.begin();
        nextTimeEvent = it->first;
    }
    else {
        moreEvents = false;
    }

    deltaStartTime = ofGetElapsedTimef();

    EventArg *evtArgs = new EventArg("/internal/playaudio", "");
    e->event(evtArgs);
}

void TimeManager::ScheduleEvent(float time, string destination, EventArg *eventArg) {
    float time_fixed = time;

    while(events.count(time_fixed) > 0) {
        time_fixed += 0.001f;
    }
    events.insert(make_pair(time_fixed, make_pair(destination, eventArg)));
}

void TimeManager::Update() {
    totalAnimTime = ofGetElapsedTimef() - deltaStartTime + timeOffset;

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
            nextTimeEvent = it->first;
        }
    }
}

void TimeManager::SetOffset(float offset) {
    timeOffset = offset;
    totalAnimTime = ofGetElapsedTimef() - deltaStartTime;

    ofLog(OF_LOG_VERBOSE, "TimeManager: offset %f", timeOffset);

    if(moreEvents && events.size() > 0) {
        //ofLog(OF_LOG_VERBOSE, "TimeManager: tiempo considerado %f", (totalAnimTime + timeOffset));
        while (( totalAnimTime + timeOffset > nextTimeEvent) && moreEvents) {
            ++it;
            if(it == events.end()) {
                moreEvents = false;
            }
            else {
                nextTimeEvent = it->first;
            }
        }
    }
}
