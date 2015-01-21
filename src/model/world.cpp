#include "model/world.h"
#include "model/organism.h"


World::World(Model* const model) : world_objects_(WorldObjectsCollection(model))
{
  auto organism = new Organism(this, AbsoluteTime(0));
  auto plane = new WorldPlane(this, Distance(1));
  world_objects_.add(organism, Coordinates(0, 0), UnitVector(0));
  world_objects_.add(plane, Coordinates(0, 0), UnitVector(0));
  event_objects_.add(organism);
}

void World::update(const AbsoluteTime &time)
{
  for (auto event_object: event_objects_)
  {
    event_object->update(time);
  }
}

const AbsoluteTime World::get_next_event_time() const
{
  AbsoluteTime earliest_event_time =
    (*event_objects_.begin())->get_next_event_time();
  for (auto event_object: event_objects_)
  {
    auto event_time = event_object->get_next_event_time();
    if (earliest_event_time > event_time)
      earliest_event_time = event_time;
  }
  return earliest_event_time;
}

const WorldObjectViewCollection World::get_objects() const
{
  return world_objects_.get_view();
}
