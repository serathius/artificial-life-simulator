#include "model/intersection.h"

bool are_intersecting(Shape &first, Shape &second)
{
  return distance(first, second) == Vector(0, 0);
}

const Vector distance(Shape &first, Shape &second)
{
  DistanceVisitor visitor(second);
  return first.accept(visitor);
}

const Vector distance(Circle &first, Circle &second)
{
  Vector centers_vector = first.coordinates - second.coordinates;
  Distance center_vector_length = centers_vector.length();
  Distance radius_sum = first.radius + second.radius;
  if (center_vector_length <= radius_sum)
  {
    return Vector(0, 0);
  }
  else
  {
    return UnitVector(centers_vector) * (center_vector_length - radius_sum);
  }
}

const Vector distance(Circle &circle, ReverseCircle &reverse_circle)
{
  Vector centers_vector = circle.coordinates - reverse_circle.coordinates;
  Distance center_vector_length = centers_vector.length();
  Distance radius_difference= reverse_circle.radius - circle.radius;
  if(radius_difference <= center_vector_length)
  {
    return Vector(0, 0);
  }
  else
  {
    return UnitVector(centers_vector) * (radius_difference - center_vector_length);
  }
}

const Vector distance(ReverseCircle &first, ReverseCircle &second)
{
  return Vector(0, 0);
}

DistanceVisitor::DistanceVisitor(Shape &shape)
  : shape_(shape)
{

}

const Vector DistanceVisitor::visit(Circle &circle)
{
  CircleVisitor visitor(circle);
  return shape_.accept(visitor);
}

const Vector DistanceVisitor::visit(ReverseCircle &reverse_circle)
{
  ReverseCircleVisitor visitor(reverse_circle);
  return shape_.accept(visitor);
}

CircleVisitor::CircleVisitor(Circle &circle) : circle_(circle)
{

}

const Vector CircleVisitor::visit(Circle &circle)
{
  return distance(circle, circle_);
}

const Vector CircleVisitor::visit(ReverseCircle &reverse_circle)
{
  return distance(circle_, reverse_circle);
}

ReverseCircleVisitor::ReverseCircleVisitor(ReverseCircle &reverse_circle) : reverse_circle_(reverse_circle)
{

}

const Vector ReverseCircleVisitor::visit(Circle &circle)
{
  return distance(circle, reverse_circle_);
}

const Vector ReverseCircleVisitor::visit(ReverseCircle &reverse_circle)
{
  return distance(reverse_circle, reverse_circle_);
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

const Vector Circle::accept(DistanceVisitorBase &visitor)
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

const Vector ReverseCircle::accept(DistanceVisitorBase &visitor)
{
  return visitor.visit(*this);
}

