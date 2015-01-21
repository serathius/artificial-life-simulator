#include "model/objects.h"

WorldObject::WorldObject(World *const world)
: world_(world)
{

}

WorldObject::~WorldObject()
{

}

WorldPlane::WorldPlane(World *const world, Distance const & distance)
  : WorldObject(world), distance_(distance)
{

}

WorldObjectView* WorldPlane::get_view(Coordinates const &coordinates,
  UnitVector const &direction)
{
  return new CircleWorldObjectView(coordinates, distance_);
}

Shape* WorldPlane::get_shape(const Coordinates& coordinates, const UnitVector&)
{
  return new ReverseCircle(coordinates, distance_);
}
