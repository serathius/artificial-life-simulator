#include "gtest/gtest.h"
#include "model/collision.h"

TEST (CollisionTest, test_circle_collide)
{
  CircleShape first(Coordinates(0, 0), Distance(1.f));
  CircleShape second(Coordinates(0, 0), Distance(1.f));
  ASSERT_TRUE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_circle_touch)
{
  CircleShape first(Coordinates(0, 0), Distance(1.f));
  CircleShape second(Coordinates(2.f, 0), Distance(1.f));
  ASSERT_FALSE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_circle_outside)
{
  CircleShape first(Coordinates(0, 0), Distance(1.f));
  CircleShape second(Coordinates(2.5f, 0), Distance(1.f));
  ASSERT_FALSE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}