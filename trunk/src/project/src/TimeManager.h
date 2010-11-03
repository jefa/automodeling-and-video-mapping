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
        static void AddTimedEvent(float time, IEventListener *eventListener, string param);

    protected:
    private:
        static map<float, pair<IEventListener*,string> > events;
};

#endif // TIMEMANAGER_H
