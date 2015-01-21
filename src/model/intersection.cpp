#include "model/intersection.h"

bool are_intersecting(Shape &first, Shape &second)
{
  IntersectionVisitor visitor(first);
  return second.accept(visitor);
}

bool are_intersecting(Circle &first, Circle &second)
{
  return first.coordinates.distance(second.coordinates) <= first.radius + second.radius;
}

bool are_intersecting(Circle &circle, ReverseCircle &reverse_circle)
{
  return reverse_circle.radius - circle.radius <=
    reverse_circle.coordinates.distance(circle.coordinates);
}
bool are_intersecting(ReverseCircle &first, ReverseCircle &second)
{
  return true;
}

IntersectionVisitor::IntersectionVisitor(Shape &shape)
  : shape_(shape)
{

}

bool IntersectionVisitor::visit(Circle &circle)
{
  CircleVisitor visitor(circle);
  return shape_.accept(visitor);
}

bool IntersectionVisitor::visit(ReverseCircle &reverse_circle)
{
  ReverseCircleVisitor visitor(reverse_circle);
  return shape_.accept(visitor);
}

CircleVisitor::CircleVisitor(Circle &circle) : circle_(circle)
{

}

bool CircleVisitor::visit(Circle &circle)
{
  return are_intersecting(circle, circle_);
}

bool CircleVisitor::visit(ReverseCircle &reverse_circle)
{
  return are_intersecting(circle_, reverse_circle);
}

ReverseCircleVisitor::ReverseCircleVisitor(ReverseCircle &reverse_circle) : reverse_circle_(reverse_circle)
{

}

bool ReverseCircleVisitor::visit(Circle &circle)
{
  return are_intersecting(circle, reverse_circle_);
}

bool ReverseCircleVisitor::visit(ReverseCircle &reverse_circle)
{
  return are_intersecting(reverse_circle, reverse_circle_);
}

Shape::~Shape()
{

}

Circle::Circle(const Coordinates &coordinates, const Distance &radius)
 : coordinates(coordinates), radius(radius)
{

}

Circle::~Circle()
{

}

bool Circle::accept(IntersectionVisitor &visitor)
{
  return visitor.visit(*this);
}

bool Circle::accept(CircleVisitor &visitor)
{
  return visitor.visit(*this);
}

bool Circle::accept(ReverseCircleVisitor &visitor)
{
  return visitor.visit(*this);
}

ReverseCircle::ReverseCircle(const Coordinates &coordinates, const Distance& radius)
  : coordinates(coordinates), radius(radius)
{
}

ReverseCircle::~ReverseCircle()
{

}

bool ReverseCircle::accept(IntersectionVisitor &visitor)
{
  return visitor.visit(*this);
}

bool ReverseCircle::accept(CircleVisitor &visitor)
{
  return visitor.visit(*this);
}

bool ReverseCircle::accept(ReverseCircleVisitor &visitor)
{
  return visitor.visit(*this);
}
