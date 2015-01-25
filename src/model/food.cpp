#include <model/objects.h>
#include "model/food.h"

Food::Food(World* const world, const FoodAmount &amount)
  :WorldObject(world), amount_(amount)
{

}

const Distance Food::get_radius()
{
  return Distance(amount_);
}

std::shared_ptr<WorldObjectView> Food::get_view(
  const Coordinates &coordinates, const UnitVector &direction)
{
  return std::shared_ptr<WorldObjectView>(
    new CircleWorldObjectView(coordinates, get_radius(), 0, {1, 1, 0}));
}

std::shared_ptr<Shape> Food::get_shape(
  const Coordinates &coordinates, const UnitVector&)
{
  return std::shared_ptr<Shape>(new Circle(coordinates, get_radius()));
}
