#ifndef EVENTS_H
#define EVENTS_H

#include <string>

class Controller;

#include "controller/realtime_clock.h"

class Event
{
public:
  Event(const RealTime &time) : time_(time) {;}
  virtual ~Event();
  const RealTime get_time() const {return time_;}
  virtual void accept(Controller *controller) = 0;
  
private:
  const RealTime time_;
};


class UpdateModelEvent : public Event
{
public:
  UpdateModelEvent(const RealTime &time) : Event(time) {;}
  virtual void accept(Controller *controller);
};

class ExitEvent: public Event
{
public:
  ExitEvent(const RealTime &time): Event(time){;}
  virtual void accept(Controller *controller);
};
#endif /* EVENTS_H */
