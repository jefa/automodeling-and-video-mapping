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
        static void Init(IEventListener *e);
        static void Update();
        static void ScheduleEvent(float time, string destination, EventArg *eventArg);

    protected:
    private:
        static map<float, pair<string, EventArg*> > events;
};

#endif // TIMEMANAGER_H
