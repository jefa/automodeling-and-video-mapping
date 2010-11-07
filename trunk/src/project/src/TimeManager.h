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
        static void Init();
        static void Update();
        static void AddTimedEvent(float time, IEventListener *evtLstnr, string opName, string param1, string param2 = "");

    protected:
    private:
        static map<float, pair<IEventListener*,EventArg*> > events;
};

#endif // TIMEMANAGER_H
