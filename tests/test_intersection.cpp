#include <common.h>
#include "gtest/gtest.h"
#include "model/intersection.h"

TEST (DistanceTest, test_circle_circle_collide)
{
  Circle first(Coordinates(0, 0), Distance(10));
  Circle second(Coordinates(0, 0), Distance(10));
  ASSERT_EQ(Vector(0, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_circle_circle_touch)
{
  Circle first(Coordinates(0, 0), Distance(10));
  Circle second(Coordinates(20.f, 0), Distance(10));
  ASSERT_EQ(Vector(0, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_circle_circle_outside)
{
  Circle first(Coordinates(0, 0), Distance(10));
  Circle second(Coordinates(25, 0), Distance(10));
  ASSERT_EQ(Vector(5, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_circle_circle_outside_reverse)
{
  Circle first(Coordinates(25, 0), Distance(10));
  Circle second(Coordinates(0, 0), Distance(10));
  ASSERT_EQ(Vector(-5, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_reverse_circle_circle_inside_symetry)
{
  Circle first(Coordinates(0, 0), Distance(10));
  ReverseCircle second(Coordinates(0, 0), Distance(15));
  ASSERT_EQ(Vector(5, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_reverse_circle_circle_inside1)
{
  Circle first(Coordinates(5, 0), Distance(10));
  ReverseCircle second(Coordinates(0, 0), Distance(20));
  ASSERT_EQ(Vector(5, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_reverse_circle_circle_inside2)
{
  Circle first(Coordinates(-5, 0), Distance(10));
  ReverseCircle second(Coordinates(0, 0), Distance(20));
  ASSERT_EQ(Vector(-5, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_reverse_circle_circle_touch1)
{
  Circle first(Coordinates(0, 0), Distance(10));
  ReverseCircle second(Coordinates(0, 0), Distance(10));
  ASSERT_EQ(Vector(0, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_reverse_circle_circle_touch2)
{
  Circle first(Coordinates(5, 0), Distance(10));
  ReverseCircle second(Coordinates(0, 0), Distance(15));
  ASSERT_EQ(Vector(0, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_reverse_circle_circle_outside)
{
  Circle first(Coordinates(0, 0), Distance(15));
  ReverseCircle second(Coordinates(0, 0), Distance(10));
  ASSERT_EQ(Vector(0, 0), distance((Shape &)first, (Shape &)second));
}

TEST (DistanceTest, test_reverse_circle_circle_intersect)
{
  Circle first(Coordinates(10, 0), Distance(10));
  ReverseCircle second(Coordinates(0, 0), Distance(15));
  ASSERT_EQ(Vector(0, 0), distance((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_circle_intersect)
{
  Circle first(Coordinates(0, 0), Distance(10));
  Circle second(Coordinates(0, 0), Distance(15));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_circle_touch)
{
  Circle first(Coordinates(0, 0), Distance(10));
  Circle second(Coordinates(25, 0), Distance(15));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_circle_outside)
{
  Circle first(Coordinates(0, 0), Distance(10));
  Circle second(Coordinates(30, 0), Distance(15));
  ASSERT_FALSE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_reverse_circle_inside)
{
  Circle first(Coordinates(0, 0), Distance(10));
  ReverseCircle second(Coordinates(0, 0), Distance(15));
  ASSERT_FALSE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_reverse_circle_touch)
{
  Circle first(Coordinates(0, 0), Distance(10));
  ReverseCircle second(Coordinates(0, 0), Distance(10));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}

TEST (IntersectionTest, test_circle_reverse_circle_outside)
{
  Circle first(Coordinates(0, 0), Distance(15));
  ReverseCircle second(Coordinates(0, 0), Distance(10));
  ASSERT_TRUE(are_intersecting((Shape &)first, (Shape &)second));
}
