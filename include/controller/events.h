#ifndef EVENTS_H
#define EVENTS_H

#include <string>

using namespace std;
class Event
{
public:
    virtual ~Event();
};

class StringEvent: public Event
{
private:
    string message;
public:
    virtual ~StringEvent();
    virtual string getMessage();
        StringEvent(string message);
};

#endif