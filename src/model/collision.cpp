#include "model/collision.h"

bool are_colliding(CollisionShape& first, CollisionShape& second)
{
  CollisionVisitor visitor(first);
  return second.accept(visitor);
}

bool are_colliding(CircleShape& first, CircleShape& second)
{
  return first.coordinates.distance(second.coordinates) < first.radius + second.radius;
}

CollisionVisitor::CollisionVisitor(CollisionShape &shape)
  : shape_(shape)
{
}

bool CollisionVisitor::visit(CircleShape& circle)
{
  CircleVisitor visitor(circle);
  return shape_.accept(visitor);
}

bool CircleVisitor::visit(CircleShape& circle)
{
  return are_colliding(circle, circle_);
}

CircleShape::CircleShape(const Coordinates &coordinates, const Distance &radius)
 : coordinates(coordinates), radius(radius)
{

}

bool CircleShape::accept(CollisionVisitor& visitor)
{
  return visitor.visit(*this);
}

bool CircleShape::accept(CircleVisitor &visitor)
{
  return visitor.visit(*this);
}
