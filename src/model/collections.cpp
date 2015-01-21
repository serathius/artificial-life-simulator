#include "model/collections.h"

void EventObjectCollection::add(EventObject *event_object)
{
  event_objects_.insert(event_object);
}

EventObjectCollection::Iterator EventObjectCollection::begin() const
{
  return event_objects_.begin();
}

EventObjectCollection::Iterator EventObjectCollection::end() const
{
  return event_objects_.end();
}
