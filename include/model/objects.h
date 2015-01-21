#ifndef OBJECTS_H_
#define OBJECTS_H_


class EventObject
{
public:
  virtual const AbsoluteTime get_next_event_time() = 0;
  virtual void update(const AbsoluteTime&) = 0;
};

#endif /* OBJECTS_H_ */
