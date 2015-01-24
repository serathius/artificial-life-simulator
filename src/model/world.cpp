#include <cassert>

#include "model/world.h"
#include "model/organism.h"


World::World(Model* const model) : world_objects_(WorldObjectsCollection())
{
  Organism* organism = new Organism(this, AbsoluteTime(0));
  WorldPlane* plane = new WorldPlane(this, Distance(1));
  add_world_object(organism, Coordinates(0, 0), UnitVector::from_degrees(0));
  add_world_object(plane, Coordinates(0, 0), UnitVector::from_degrees(0));
  add_event_object(organism);
  allocated_objects_.push_back(std::shared_ptr<WorldObject>(organism));
  allocated_objects_.push_back(std::shared_ptr<WorldObject>(plane));
}

void World::add_world_object(WorldObject* object,
  Coordinates const &coordinates, UnitVector const &direction)
{
  assert(has_free_space(object, coordinates, direction));
  world_objects_.insert(std::pair<WorldObject*, Position>(object, {coordinates, direction}));
}

void World::add_event_object(EventObject* object)
{
  event_objects_.insert(object);
}

void World::remove_world_object(WorldObject *object)
{
  world_objects_.erase(object);
}

void World::remove_event_object(EventObject *object)
{
  event_objects_.erase(object);
}

bool World::has_free_space(WorldObject* object,
  Coordinates const &coordinates, UnitVector const &direction)
{
  std::shared_ptr<Shape> first_shape = object->get_shape(coordinates, direction);
  std::shared_ptr<Shape> second_shape;
  for (auto pair: world_objects_)
  {
    if (object != pair.first)
    {
      second_shape = pair.first->get_shape(pair.second.coordinates,
        pair.second.direction);
      if (are_intersecting(*first_shape, *second_shape)) {
        return false;
      }
    }
  }
  return true;
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
  if (event_objects_.begin() == event_objects_.end())
  {
    LOG("dsadasdasdasda");
    throw InfiniteRealTime();
  }
  else
  {
    AbsoluteTime earliest_event_time =
      (*event_objects_.begin())->get_next_event_time();
    for (auto event_object: event_objects_) {
      LOG(event_object);
      auto event_time = event_object->get_next_event_time();
      if (earliest_event_time > event_time)
      {
        earliest_event_time = event_time;
      }
    }
    return earliest_event_time;
  }
}

const WorldObjectViewCollection World::get_objects() const
{
  WorldObjectViewCollection result;
  for (auto pair: world_objects_)
  {
    std::shared_ptr<WorldObjectView> view_object = pair.first->get_view(
      pair.second.coordinates, pair.second.direction);
    result.push_back(view_object);
  }
  return result;
}

void World::move_object_forward(WorldObject* object, const Distance &distance)
{
  WorldObjectsCollection::iterator it = world_objects_.find(object);
  assert(it != world_objects_.end());
  auto new_coordinates = it->second.coordinates + it->second.direction * distance;
  LOG(has_free_space(object, it->second.coordinates, it->second.direction));
  if(has_free_space(object, new_coordinates, it->second.direction))
  {
    it->second.coordinates = new_coordinates;
    LOG(it->second.coordinates);
  }
  LOG(world_objects_.find(object)->second.coordinates);
}

void World::rotate_object(WorldObject* object, UnitVector const & angle)
{
  WorldObjectsCollection::iterator it = world_objects_.find(object);
  assert(it != world_objects_.end());
  UnitVector new_direction = it->second.direction + angle;
  if(has_free_space(object, it->second.coordinates, new_direction))
  {
    it->second.direction = new_direction;
  }
}
