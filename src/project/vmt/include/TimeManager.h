#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "ISerializable.h"

#include <map>
#include <string>
using namespace std;

class TimeManager : public ISerializable
{
    public:
        TimeManager();
        virtual ~TimeManager();
        void Start();
        string Update();
        void ScheduleEvent(float time, string effectId);

        virtual SerializedNode* Serialize();
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
