#ifndef INTERSECTION_H
#define INTERSECTION_H

struct Shape;
struct Circle;
struct Rectangle;

#include "primitives.h"

bool are_intersecting(Shape& first, Shape& second);
bool are_intersecting(Circle& first, Circle& second);
bool are_intersecting(Rectangle& first, Rectangle& second);
bool are_intersecting(Circle& first, Rectangle& second);

class IntersectionVisitorBase
{
public:
  virtual bool visit(Circle&) = 0;
  virtual bool visit(Rectangle&) = 0;

};

class IntersectionVisitor : public IntersectionVisitorBase
{
private:
  Shape& shape_;

public:
  IntersectionVisitor(Shape&);
  virtual bool visit(Circle&);
  virtual bool visit(Rectangle&);
};

class CircleVisitor : public IntersectionVisitorBase
{
private:
  Circle& circle_;

public:
  CircleVisitor(Circle&);
  virtual bool visit(Circle&);
  virtual bool visit(Rectangle&);
};

class RectangleVisitor : public IntersectionVisitorBase
{
private:
  Rectangle& rectangle_;

public:
  RectangleVisitor(Rectangle&);
  virtual bool visit(Circle&);
  virtual bool visit(Rectangle&);
};

class Shape
{
public:
  virtual bool accept(IntersectionVisitor& visitor) = 0;
  virtual bool accept(CircleVisitor& visitor) = 0;
  virtual bool accept(RectangleVisitor& visitor) = 0;
};

struct Circle : public Shape
{
  Circle(const Coordinates& coordinates, const Distance& radius);
  virtual bool accept(IntersectionVisitor& visitor);
  virtual bool accept(CircleVisitor& visitor);
  virtual bool accept(RectangleVisitor& visitor);

  const Coordinates coordinates;
  const Distance radius;
};

struct Rectangle : public Shape
{
  Rectangle(const Coordinates& coordinates, const UnitVector& direction,
    const Dimension& dimension);
  virtual bool accept(IntersectionVisitor& visitor);
  virtual bool accept(CircleVisitor& visitor);
  virtual bool accept(RectangleVisitor& visitor);

  const Coordinates coordinates;
  const UnitVector direction;
  const Dimension dimension;
};

#endif /* INTERSECTION_H_ */
