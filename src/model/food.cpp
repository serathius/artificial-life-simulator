#include <random>

#include "model/food.h"
#include "model/world.h"

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

FoodController::FoodController(World *world, WorldPlane *plane,
  const AbsoluteTime &time)
  : world_(world), plane_(plane), last_food_spawn_time_(time)
{
}

const AbsoluteTime FoodController::get_next_event_time()
{
  if (foods_.size() < MAX_FOOD_PILES_COUNT) {
    return last_food_spawn_time_ + TimeDifference::seconds(SPAWN_COOLDOWN_SECONDS);
  }
  else
  {
    return AbsoluteTime::get_max();
  }
}

void FoodController::update(AbsoluteTime const &time)
{

  if(time>= last_food_spawn_time_ + TimeDifference::seconds(SPAWN_COOLDOWN_SECONDS)
    && foods_.size() < MAX_FOOD_PILES_COUNT)
  {
    last_food_spawn_time_ = time;
    Food* food = new Food(world_, 0.1);
    while(true)
    {
      Coordinates coordinates = plane_->get_random_position();
      LOG(coordinates);
      try
      {
        world_->register_world_object(food, coordinates, UnitVector::from_degrees(0));
        foods_.push_back(food);
        return;
      }
      catch (NoSpace)
      {

      }
    }
  }
}

const FoodCollection& FoodController::get_foods() const
{
  return foods_;
}