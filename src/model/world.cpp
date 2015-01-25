#include <cassert>

#include "model/world.h"
#include "model/organism.h"

World::World(Model* const model) : world_objects_(WorldObjectsCollection())
{
  Organism *organism = new Organism(this, AbsoluteTime(0));
  WorldPlane *plane = new WorldPlane(this, Distance(1));
  food_controller_ = new FoodController(this, plane, AbsoluteTime(0));
  register_world_object(organism, Coordinates(0, 0), UnitVector::from_degrees(0));
  register_world_object(plane, Coordinates(0, 0), UnitVector::from_degrees(0));
  register_event_object(organism);
  register_event_object(food_controller_);
}


World::~World()
{
  for (auto object: allocated_objects_)
  {
    delete object;
  }
}

void World::register_world_object(WorldObject *object,
  Coordinates const &coordinates, UnitVector const &direction)
{
  allocated_objects_.insert(object);
  if(!has_free_space(object, coordinates, direction))
  {
    throw NoSpace();
  }
  world_objects_.insert(std::pair<WorldObject*, Position>(object, {coordinates, direction}));
}

void World::register_event_object(EventObject *object)
{
  event_objects_.insert(object);
  allocated_objects_.insert(object);
}

void World::deregister_world_object(WorldObject *object)
{
  world_objects_.erase(object);
}

void World::deregister_event_object(EventObject *object)
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
  AbsoluteTime earliest_event_time = AbsoluteTime::get_max();
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
  if(has_free_space(object, new_coordinates, it->second.direction))
  {
    it->second.coordinates = new_coordinates;
  }
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

std::vector<std::pair<Food*, const Vector>> World::get_relative_foods_position(
  WorldObject *object) const
{
  std::vector<std::pair<Food*, const Vector>> relative_food_position;
  Position object_position= world_objects_.at(object);
  std::shared_ptr<Shape> object_shape= object->get_shape(
    object_position.coordinates, object_position.direction);

  for (auto food: food_controller_->get_foods())
  {
    Position food_position = world_objects_.at(dynamic_cast<WorldObject*>(food));
    std::shared_ptr<Shape> food_shape = food->get_shape(
      food_position.coordinates, food_position.direction);
    relative_food_position.push_back(
      std::pair<Food*, const Vector>(food, distance(*object_shape, *food_shape)));
  }
  return relative_food_position;
}
