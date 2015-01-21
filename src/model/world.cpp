#include <assert.h>
#include "model/world.h"

#include "model/organism.h"


World::World(Model* const model) : objects_(WorldObjectsCollection(model))
{
  assert(objects_.add(
    new WorldPlane(this, Distance(1)), Coordinates(0, 0), UnitVector(0)));
  assert(objects_.add(
    new Organism(this, AbsoluteTime(0)), Coordinates(0, 0), UnitVector(0)));
}

const WorldObjectViewCollection World::get_objects() const
{
  return objects_.get_view();
}
