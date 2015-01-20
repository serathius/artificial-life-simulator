#include "gtest/gtest.h"
#include "model/intersection.h"

TEST (IntersectionTest, test_circle_circle_collide)
{
  Circle first(Coordinates(0, 0), Distance(1.f));
  Circle second(Coordinates(0, 0), Distance(1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_circle_touch)
{
  Circle first(Coordinates(0, 0), Distance(1.f));
  Circle second(Coordinates(2.f, 0), Distance(1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_circle_outside)
{
  Circle first(Coordinates(0, 0), Distance(1.f));
  Circle second(Coordinates(2.5f, 0), Distance(1.f));
  ASSERT_FALSE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_reverse_circle_circle_inside1)
{
  Circle first(Coordinates(0, 0), Distance(1.f));
  ReverseCircle second(Coordinates(0, 0), Distance(1.5f));
  ASSERT_FALSE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_reverse_circle_circle_inside2)
{
  Circle first(Coordinates(0.5, 0), Distance(1.f));
  ReverseCircle second(Coordinates(0, 0), Distance(2.f));
  ASSERT_FALSE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_reverse_circle_circle_touch1)
{
  Circle first(Coordinates(0, 0), Distance(1.f));
  ReverseCircle second(Coordinates(0, 0), Distance(1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_reverse_circle_circle_touch2)
{
  Circle first(Coordinates(0.5f, 0), Distance(1.f));
  ReverseCircle second(Coordinates(0, 0), Distance(1.5f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_reverse_circle_circle_outside)
{
  Circle first(Coordinates(0, 0), Distance(1.5f));
  ReverseCircle second(Coordinates(0, 0), Distance(1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}
TEST (IntersectionTest, test_reverse_circle_circle_intersect)
{
  Circle first(Coordinates(1.f, 0), Distance(1.f));
  ReverseCircle second(Coordinates(0, 0), Distance(1.5f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}
