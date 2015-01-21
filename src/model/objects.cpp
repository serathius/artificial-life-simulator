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

WorldObjectView* WorldPlane::get_view(const Coordinates &coordinates,
const UnitVector &direction)
{
  return new CircleWorldObjectView(coordinates, distance_);
}

Shape* WorldPlane::get_shape(const Coordinates &coordinates, const UnitVector&)
{
  return new ReverseCircle(coordinates, distance_);
}
