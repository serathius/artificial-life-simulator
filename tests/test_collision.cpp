#include "gtest/gtest.h"
#include "model/collision.h"

TEST (CollisionTest, test_circle_circle_collide)
{
  CircleShape first(Coordinates(0, 0), Distance(1.f));
  CircleShape second(Coordinates(0, 0), Distance(1.f));
  ASSERT_TRUE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_circle_circle_touch)
{
  CircleShape first(Coordinates(0, 0), Distance(1.f));
  CircleShape second(Coordinates(2.f, 0), Distance(1.f));
  ASSERT_TRUE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_circle_circle_outside)
{
  CircleShape first(Coordinates(0, 0), Distance(1.f));
  CircleShape second(Coordinates(2.5f, 0), Distance(1.f));
  ASSERT_FALSE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_rectangle_circle_collide)
{
  RectangleShape first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  CircleShape second(Coordinates(0, 0), Distance(1.f));
  ASSERT_TRUE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_circle_rectangle_collide)
{
  CircleShape first(Coordinates(0, 0), Distance(1.f));
  RectangleShape second(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_TRUE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_rectangle_circle_touch)
{
  RectangleShape first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  CircleShape second(Coordinates(1.5f, 0), Distance(1.f));
  ASSERT_TRUE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_circle_rectangle_touch)
{
  CircleShape first(Coordinates(1.5f, 0), Distance(1.f));
  RectangleShape second(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_TRUE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_rectangle_circle_outside)
{
  RectangleShape first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  CircleShape second(Coordinates(2.f, 0), Distance(1.f));
  ASSERT_FALSE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_circle_rectangle_outside) {
  CircleShape first(Coordinates(2.f, 0), Distance(1.f));
  RectangleShape second(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_FALSE(are_colliding((CollisionShape &) first, (CollisionShape &) second));
}

TEST (CollisionTest, test_rectangle_rectangle_collide)
{
  RectangleShape first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  RectangleShape second(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_TRUE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_rectangle_rectangle_touch)
{
  RectangleShape first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  RectangleShape second(Coordinates(1.f, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_TRUE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}

TEST (CollisionTest, test_rectangle_rectangle_outside)
{
  RectangleShape first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  RectangleShape second(Coordinates(2.f, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_FALSE(are_colliding((CollisionShape&)first, (CollisionShape&)second));
}
