#ifndef INTERSECTION_H
#define INTERSECTION_H

struct Shape;
struct Circle;
struct ReverseCircle;

#include "primitives.h"

bool are_intersecting(Shape &first, Shape &second);

const Vector distance(Shape &first, Shape &second);
const Vector distance(Circle &first, Circle &second);
const Vector distance(Circle &first, ReverseCircle &second);
const Vector distance(ReverseCircle &first, ReverseCircle &second);


class DistanceVisitorBase
{
public:
  virtual const Vector visit(Circle&) = 0;
  virtual const Vector visit(ReverseCircle&) = 0;

};

class DistanceVisitor : public DistanceVisitorBase
{
public:
  DistanceVisitor(Shape&);
  virtual const Vector visit(Circle&);
  virtual const Vector visit(ReverseCircle&);

private:
  Shape &shape_;
};

class CircleVisitor : public DistanceVisitorBase
{
public:
  CircleVisitor(Circle&);
  virtual const Vector visit(Circle&);
  virtual const Vector visit(ReverseCircle&);

private:
  Circle &circle_;
};

class ReverseCircleVisitor : public DistanceVisitorBase
{
public:
  ReverseCircleVisitor(ReverseCircle&);
  virtual const Vector visit(Circle&);
  virtual const Vector visit(ReverseCircle&);

private:
  ReverseCircle &reverse_circle_;
};

class Shape
{
public:
  virtual ~Shape();
  virtual const Vector accept(DistanceVisitorBase&) = 0;
};

struct Circle : public Shape
{
  Circle(const Coordinates&, const Distance &radius);
  ~Circle();
  virtual const Vector accept(DistanceVisitorBase&);

  const Coordinates coordinates;
  const Distance radius;
};

struct ReverseCircle : public Shape
{
  ReverseCircle(const Coordinates&, const Distance&);
  ~ReverseCircle();
  virtual const Vector accept(DistanceVisitorBase&);

  const Coordinates coordinates;
  const Distance radius;
};

#endif /* INTERSECTION_H_ */
