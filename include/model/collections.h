#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <set>
#include <map>
#include <memory>

#include "objects.h"
#include "primitives.h"

typedef std::set<std::shared_ptr<EventObject>> EventObjectCollection;


struct Position
{
  Coordinates coordinates;
  UnitVector direction;
};


typedef std::map<std::shared_ptr<WorldObject>, Position> WorldObjectsCollection;

#endif /* COLLECTIONS_H_ */
