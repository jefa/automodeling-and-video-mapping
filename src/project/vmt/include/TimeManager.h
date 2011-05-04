#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <map>
#include <string>
using namespace std;

class TimeManager
{
    public:
        TimeManager();
        virtual ~TimeManager();
        void Start();
        string Update();
        void ScheduleEvent(float time, string effectId);
    protected:
    private:
        map<float, string> events;
        map<float, string>::iterator it;

        double totalAnimTime;
        double deltaStartTime;       //Tiempo entre que comenzó la aplicación y se hizo init a TimeManager

        float nextTimeEvent;
        float timeOffset;
        bool moreEvents;
        bool started;
};

#endif // TIMEMANAGER_H
