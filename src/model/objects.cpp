#include "model/objects.h"

WorldObject::WorldObject(World *const world)
: world_(world)
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
