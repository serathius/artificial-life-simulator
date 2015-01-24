#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <set>
#include <map>
#include <memory>

#include "objects.h"
#include "primitives.h"

typedef std::set<EventObject*> EventObjectCollection;


struct Position
{
  Coordinates coordinates;
  UnitVector direction;
};


typedef std::map<WorldObject*, Position> WorldObjectsCollection;

#endif /* COLLECTIONS_H_ */
