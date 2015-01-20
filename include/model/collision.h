#ifndef COLLISION_H
#define COLLISION_H

struct CollisionShape;
struct CircleShape;

#include "primitives.h"

bool are_colliding(CollisionShape& first, CollisionShape& second);
bool are_colliding(CircleShape& first, CircleShape& second);

class CollisionVisitorBase
{
public:
  virtual bool visit(CircleShape&) = 0;
};

class CollisionVisitor : public CollisionVisitorBase
{
private:
  CollisionShape& shape_;

public:
  CollisionVisitor(CollisionShape& shape);
  virtual bool visit(CircleShape& circle);
};

class CircleVisitor : public CollisionVisitorBase
{
private:
  CircleShape& circle_;

public:
  CircleVisitor(CircleShape& circle) : circle_(circle){}
  virtual bool visit(CircleShape& circle);
};

class CollisionShape
{
public:
  virtual bool accept(CollisionVisitor& visitor) = 0;
  virtual bool accept(CircleVisitor& visitor) = 0;
};

struct CircleShape : public CollisionShape
{
  CircleShape(const Coordinates& coordinates, const Distance& radius);
  virtual bool accept(CollisionVisitor& visitor);
  virtual bool accept(CircleVisitor& visitor);

  const Coordinates coordinates;
  const Distance radius;
};


#endif /* COLLISION_H_ */
