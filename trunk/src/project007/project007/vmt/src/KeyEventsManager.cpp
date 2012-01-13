#include "KeyEventsManager.h"

KeyEventsManager::KeyEventsManager()
{
    //ctor
}

KeyEventsManager::~KeyEventsManager()
{
    //dtor
}

void KeyEventsManager::addKeyEvent(char key, string effectId) {
    events.insert(pair<char,string>(key,effectId));
}

bool KeyEventsManager::hasKeyEvent(char key) {
    return events.count(key) > 0;
}

string KeyEventsManager::getEffectId(char key) {
    return events[key];
}

SerializedNode* KeyEventsManager::Serialize() {
    SerializedNode *node = new SerializedNode("keyevents");

    map<char, string>::iterator eventsIt;
    for(eventsIt = events.begin(); eventsIt != events.end(); eventsIt++) {
        SerializedNode *eventNode = new SerializedNode("keyevent");
        eventNode->addAttribute("key", eventsIt->first);
        eventNode->addAttribute("effect", eventsIt->second);
        node->addChildNode(eventNode);
    }

    return node;
}

map<char, string> KeyEventsManager::getKeyEvents(){
    return events;
}
