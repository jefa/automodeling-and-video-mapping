#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "IEventListener.h"

#include <string>
#include <map>

using namespace std;

class TimeManager
{
    public:
        TimeManager();
        virtual ~TimeManager();
        static void Init(IEventListener *e/*, float offset=0*/);
        static void Update();
        static void ScheduleEvent(float time, string destination, EventArg *eventArg);
        static void SetOffset(float timeOffset);

    protected:
    private:
        static map<float, pair<string, EventArg*> > events;
};

#endif // TIMEMANAGER_H
