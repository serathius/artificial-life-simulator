#include <cassert>

#include "model/world.h"
#include "model/organism.h"


World::World(Model* const model) : world_objects_(WorldObjectsCollection())
{
  std::shared_ptr<Organism> organism = std::shared_ptr<Organism>(new Organism(this, AbsoluteTime(0)));
  std::shared_ptr<WorldPlane> plane = std::shared_ptr<WorldPlane>(new WorldPlane(this, Distance(1)));
  add_world_object(organism, Coordinates(0, 0), UnitVector::from_degrees(0));
  add_world_object(plane, Coordinates(0, 0), UnitVector::from_degrees(0));
  add_event_object(organism);
}

void World::add_world_object(std::shared_ptr<WorldObject> object,
  Coordinates const &coordinates, UnitVector const &direction)
{
  std::shared_ptr<Shape> first_shape = object->get_shape(coordinates, direction);
  std::shared_ptr<Shape> second_shape;
  for (auto pair: world_objects_)
  {
    second_shape = pair.first->get_shape(pair.second.coordinates,
      pair.second.direction);
    assert(!are_intersecting(*first_shape, *second_shape));
  }
  world_objects_.insert(std::pair<std::shared_ptr<WorldObject>, Position>(object, {coordinates, direction}));
}

void World::add_event_object(std::shared_ptr<EventObject> object)
{
  event_objects_.insert(object);
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
  WorldObjectViewCollection result;
  for (auto pair: world_objects_)
  {
    WorldObjectView* view_object = pair.first->get_view(
      pair.second.coordinates, pair.second.direction);
    result.push_back(std::shared_ptr<WorldObjectView>(view_object));
  }
  return result;
}
