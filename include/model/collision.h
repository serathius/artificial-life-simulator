#ifndef COLLISION_H
#define COLLISION_H

struct CollisionShape;
struct CircleShape;
struct RectangleShape;

#include "primitives.h"

bool are_colliding(CollisionShape& first, CollisionShape& second);
bool are_colliding(CircleShape& first, CircleShape& second);
bool are_colliding(RectangleShape& first, RectangleShape& second);
bool are_colliding(CircleShape& first, RectangleShape& second);

class CollisionVisitorBase
{
public:
  virtual bool visit(CircleShape&) = 0;
  virtual bool visit(RectangleShape&) = 0;

};

class CollisionVisitor : public CollisionVisitorBase
{
private:
  CollisionShape& shape_;

public:
  CollisionVisitor(CollisionShape&);
  virtual bool visit(CircleShape&);
  virtual bool visit(RectangleShape&);
};

class CircleVisitor : public CollisionVisitorBase
{
private:
  CircleShape& circle_;

public:
  CircleVisitor(CircleShape&);
  virtual bool visit(CircleShape&);
  virtual bool visit(RectangleShape&);
};

class RectangleVisitor : public CollisionVisitorBase
{
private:
  RectangleShape& rectangle_;

public:
  RectangleVisitor(RectangleShape&);
  virtual bool visit(CircleShape&);
  virtual bool visit(RectangleShape&);
};

class CollisionShape
{
public:
  virtual bool accept(CollisionVisitor& visitor) = 0;
  virtual bool accept(CircleVisitor& visitor) = 0;
  virtual bool accept(RectangleVisitor& visitor) = 0;
};

struct CircleShape : public CollisionShape
{
  CircleShape(const Coordinates& coordinates, const Distance& radius);
  virtual bool accept(CollisionVisitor& visitor);
  virtual bool accept(CircleVisitor& visitor);
  virtual bool accept(RectangleVisitor& visitor);

  const Coordinates coordinates;
  const Distance radius;
};

struct RectangleShape : public CollisionShape
{
  RectangleShape(const Coordinates& coordinates, const UnitVector& direction,
    const Dimension& dimension);
  virtual bool accept(CollisionVisitor& visitor);
  virtual bool accept(CircleVisitor& visitor);
  virtual bool accept(RectangleVisitor& visitor);

  const Coordinates coordinates;
  const UnitVector direction;
  const Dimension dimension;
};

#endif /* COLLISION_H_ */
