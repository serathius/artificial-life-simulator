#include <string>

#ifndef EVENTS_H
#define EVENTS_H

class Controller;

#include "controller/realtime_clock.h"

class Event
{
private:
    const RealTime time_;

public:
    Event(const RealTime& time) : time_(time) {;}
    const RealTime get_time() const {return time_;}
    virtual void accept(Controller* controller) = 0;
    virtual ~Event();
};


class UpdateModelEvent : public Event
{
public:
    UpdateModelEvent(const RealTime& time) : Event(time) {;}
    virtual void accept(Controller* controller);
};

#endif
