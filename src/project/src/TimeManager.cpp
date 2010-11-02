#include "TimeManager.h"

#include "ofAppRunner.h"

static double totalAnimTime;
static double deltaStartTime;       //Tiempo entre que comenzó la aplicación y se hizo init a TimeManager
static map<float, string>::iterator it;
static float nextTimeEvent;

map<float, string> TimeManager::events;

TimeManager::TimeManager()
{
    //ctor
}

TimeManager::~TimeManager()
{
    //dtor
}

void TimeManager::Init() {
    events.insert(make_pair(2.0, "1er evento"));
    events.insert(make_pair(3.3, "2do evento"));
    events.insert(make_pair(8.8, "4to evento"));
    events.insert(make_pair(6.2, "3er evento"));

    totalAnimTime = 0;
    it = events.begin();
    nextTimeEvent = (*it).first;
    deltaStartTime = ofGetElapsedTimef();
}

void TimeManager::Update() {
    totalAnimTime = ofGetElapsedTimef() - deltaStartTime;

    if(totalAnimTime > nextTimeEvent && events.size() > 0) {
        map<float, string>::iterator it2 = it;
        ofLog(OF_LOG_VERBOSE, (*it).second);
        ++it;
        events.erase(it2);
        nextTimeEvent = (*it).first;
    }
}
