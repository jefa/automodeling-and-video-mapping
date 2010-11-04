#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "IEventListener.h"
#include "TimedEventArg.h"

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
        static void AddTimedEvent(float time, IEventListener *eventListener, string opName, string param);

    protected:
    private:
        static map<float, pair<IEventListener*,TimedEventArg*> > events;
};

#endif // TIMEMANAGER_H
