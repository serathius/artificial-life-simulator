#include <random>
#include <model/world.h>

#include "model/objects.h"

Object::~Object()
{

}

WorldObject::WorldObject(World *const world)
: world_(world)
{

}

EventObject::~EventObject()
{

}

WorldObject::~WorldObject()
{

}

WorldPlane::WorldPlane(World *const world, const Distance &distance)
  : WorldObject(world), distance_(distance)
{

}

std::shared_ptr<WorldObjectView> WorldPlane::get_view(
  const Coordinates &coordinates, const UnitVector &direction)
{
  return std::shared_ptr<WorldObjectView>(
    new CircleWorldObjectView(coordinates, distance_, -1, {0, 0.5, 0}));
}

std::shared_ptr<Shape> WorldPlane::get_shape(
  const Coordinates &coordinates, const UnitVector&)
{
  return std::shared_ptr<Shape>(new ReverseCircle(coordinates, distance_));
}

const Coordinates WorldPlane::get_random_position() const
{
  UnitVector random_direction = UnitVector::from_degrees(
    std::uniform_real_distribution<float>(0, 180)(
      world_->random_generator_engine_));
  Distance random_distance = Distance(
    std::uniform_real_distribution<float>(0, distance_.get_distance())(
      world_->random_generator_engine_));
  return Coordinates(0,0) + random_direction * random_distance;
}
