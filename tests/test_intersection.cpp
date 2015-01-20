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

TEST (IntersectionTest, test_rectangle_circle_collide)
{
  Rectangle first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  Circle second(Coordinates(0, 0), Distance(1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_rectangle_collide)
{
  Circle first(Coordinates(0, 0), Distance(1.f));
  Rectangle second(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_rectangle_circle_touch)
{
  Rectangle first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  Circle second(Coordinates(1.5f, 0), Distance(1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_rectangle_touch)
{
  Circle first(Coordinates(1.5f, 0), Distance(1.f));
  Rectangle second(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_rectangle_circle_outside)
{
  Rectangle first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  Circle second(Coordinates(2.f, 0), Distance(1.f));
  ASSERT_FALSE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_rectangle_outside) {
  Circle first(Coordinates(2.f, 0), Distance(1.f));
  Rectangle second(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_FALSE(are_intersecting((Shape &) first, (Shape &) second));
}

TEST (IntersectionTest, test_rectangle_rectangle_collide)
{
  Rectangle first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  Rectangle second(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_rectangle_rectangle_touch)
{
  Rectangle first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  Rectangle second(Coordinates(1.f, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_rectangle_rectangle_outside)
{
  Rectangle first(Coordinates(0, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  Rectangle second(Coordinates(2.f, 0), UnitVector(0.f), Dimension(1.f, 1.f));
  ASSERT_FALSE(are_intersecting((Shape &)first, (Shape &)second));
}
