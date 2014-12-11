#include <string>

#ifndef EVENTS_H
#define EVENTS_H

class Event
{
public:
    virtual ~Event();
};

class StringEvent: public Event
{
private:
    std::string message;
public:
    virtual ~StringEvent();
    virtual std::string getMessage();
        StringEvent(std::string message);
};

#endif
