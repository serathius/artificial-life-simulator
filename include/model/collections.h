#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <set>

#include "objects.h"

class EventObjectCollection
{
public:
  typedef std::set<EventObject*>::iterator Iterator;

  Iterator begin() const;
  Iterator end() const;
  void add(EventObject*);
  void remove(EventObject*);

private:
  std::set<EventObject*> event_objects_;
};

#endif /* COLLECTIONS_H_ */
