#include "TimeManager.h"
#include "ofAppRunner.h"

TimeManager::TimeManager() {
    started = false;
}

TimeManager::~TimeManager() {
}

void TimeManager::Start() {
    totalAnimTime = 0;

    if(events.size() > 0) {
        it = events.begin();
        nextTimeEvent = it->first;
    }
    else {
        moreEvents = false;
    }

    deltaStartTime = ofGetElapsedTimef();
    started = true;
}

void TimeManager::ScheduleEvent(float time, string effectId) {
    moreEvents = true;
    float time_fixed = time;
    while(events.count(time_fixed) > 0) {
        time_fixed += 0.001f;
    }
    events.insert(make_pair(time_fixed, effectId));
}

string TimeManager::Update() {
    string effectId = "";

    if(!started)
        return effectId;

    totalAnimTime = ofGetElapsedTimef() - deltaStartTime;

    if(moreEvents && events.size() > 0 && totalAnimTime > nextTimeEvent) {
        effectId = it->second;
        ++it;
        if(it == events.end()) {
            moreEvents = false;
        }
        else {
            nextTimeEvent = it->first;
        }
    }

    return effectId;
}

SerializedNode* TimeManager::Serialize() {
    SerializedNode *node = new SerializedNode("timedevents");

    map<float, string>::iterator eventsIt;
    for(eventsIt = events.begin(); eventsIt != events.end(); eventsIt++) {
        SerializedNode *eventNode = new SerializedNode("timedevent");
        eventNode->addAttribute("t", eventsIt->first);
        eventNode->addAttribute("effect", eventsIt->second);
        node->addChildNode(eventNode);
    }

    return node;
}
