#include "model/intersection.h"

#include <cassert>
#include <cmath>

bool are_intersecting(Shape & first, Shape & second)
{
  IntersectionVisitor visitor(first);
  return second.accept(visitor);
}

bool are_intersecting(Circle & first, Circle & second)
{
  return first.coordinates.distance(second.coordinates) <= first.radius + second.radius;
}

bool are_intersecting(Circle & circle, Rectangle & rectangle)
{
  float distance_x = abs(circle.coordinates.get_x() - rectangle.coordinates.get_x());
  float distance_y = abs(circle.coordinates.get_y() - rectangle.coordinates.get_y());

  if (distance_x > (rectangle.dimension.get_x() / 2 + circle.radius.get_distance())
    || distance_y > (rectangle.dimension.get_y() / 2 + circle.radius.get_distance()))
  {
    return false;
  }

  if (distance_x <= (rectangle.dimension.get_x() / 2)
    || distance_y <= (rectangle.dimension.get_y() / 2))
  {
    return true;
  }

  float corner_distance_x = powf(distance_x - rectangle.dimension.get_x() / 2, 2);
  float corner_distance_y = powf(distance_y - rectangle.dimension.get_y() / 2, 2);

  return (corner_distance_x + corner_distance_y <= (
    circle.radius.get_distance() * circle.radius.get_distance()));
}

bool are_intersecting(Rectangle & first, Rectangle & second)
{
  float first_point1x = first.coordinates.get_x() - first.dimension.get_x() / 2;
  float first_point1y = first.coordinates.get_y() - first.dimension.get_y() / 2;
  float first_point2x = first.coordinates.get_x() + first.dimension.get_x() / 2;
  float first_point2y = first.coordinates.get_y() + first.dimension.get_y() / 2;
  float second_point1x = second.coordinates.get_x() - second.dimension.get_x() / 2;
  float second_point1y = second.coordinates.get_y() - second.dimension.get_y() / 2;
  float second_point2x = second.coordinates.get_x() + second.dimension.get_x() / 2;
  float second_point2y = second.coordinates.get_y() + second.dimension.get_y() / 2;
  bool first_x_overlap = second_point1x >= first_point1x && second_point1x <= first_point2x;
  bool second_x_overlap = first_point1x >= second_point1x && first_point1x <= second_point2x;

  bool first_y_overlap = second_point1y >= first_point1y && second_point1y <= first_point2y;
  bool second_y_overlap = first_point1y >= second_point1y && first_point1y <= second_point2y;

  return (first_x_overlap || second_x_overlap) && (first_y_overlap || second_y_overlap);
}

IntersectionVisitor::IntersectionVisitor(Shape &shape)
  : shape_(shape)
{

}

bool IntersectionVisitor::visit(Circle & circle)
{
  CircleVisitor visitor(circle);
  return shape_.accept(visitor);
}

bool IntersectionVisitor::visit(Rectangle & rectangle)
{
  RectangleVisitor visitor(rectangle);
  return shape_.accept(visitor);
}

CircleVisitor::CircleVisitor(Circle &circle) : circle_(circle)
{

}

bool CircleVisitor::visit(Circle & circle)
{
  return are_intersecting(circle, circle_);
}

bool CircleVisitor::visit(Rectangle & rectangle)
{
  return are_intersecting(circle_, rectangle);
}

RectangleVisitor::RectangleVisitor(Rectangle &rectangle) : rectangle_(rectangle)
{

}

bool RectangleVisitor::visit(Circle &circle)
{
  return are_intersecting(circle, rectangle_);
}

bool RectangleVisitor::visit(Rectangle &rectangle)
{
  return are_intersecting(rectangle, rectangle_);
}

Circle::Circle(const Coordinates &coordinates, const Distance &radius)
 : coordinates(coordinates), radius(radius)
{

}

bool Circle::accept(IntersectionVisitor & visitor)
{
  return visitor.visit(*this);
}

bool Circle::accept(CircleVisitor &visitor)
{
  return visitor.visit(*this);
}

bool Circle::accept(RectangleVisitor& visitor)
{
  return visitor.visit(*this);
}

Rectangle::Rectangle(const Coordinates &coordinates,
  const UnitVector &direction, const Dimension& dimension)
  : coordinates(coordinates), direction(direction), dimension(dimension)
{
  assert(direction == UnitVector(0));
}

bool Rectangle::accept(IntersectionVisitor & visitor)
{
  return visitor.visit(*this);
}

bool Rectangle::accept(CircleVisitor &visitor)
{
  return visitor.visit(*this);
}

bool Rectangle::accept(RectangleVisitor& visitor)
{
  return visitor.visit(*this);
}
