#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

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
    protected:
    private:
        static map<float, string> events;
};

#endif // TIMEMANAGER_H
