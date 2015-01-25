#include <random>

#include "model/food.h"

FoodPile::FoodPile(World* const world, FoodController *controller)
  :WorldObject(world), amount_(FOOD_PER_PILE), controller_(controller)
{

}

const Distance FoodPile::get_radius()
{
  return Distance(amount_ * RADIUS_PER_FOOD);
}

WorldObjectViewCollection FoodPile::get_view(
  const Coordinates &coordinates, const UnitVector &direction)
{
  WorldObjectViewCollection world_object_view;
  world_object_view.push_back(std::shared_ptr<ViewElement>(
    new CircleViewElement(coordinates, get_radius(), 0, {1, 1, 0})));
  return world_object_view;
}

std::shared_ptr<Shape> FoodPile::get_shape(
  const Coordinates &coordinates, const UnitVector&)
{
  return std::shared_ptr<Shape>(new Circle(coordinates, get_radius()));
}

const Energy FoodPile::eat(const TimeDifference& time)
{
  FoodAmount food_eaten;
  FoodAmount maximum_food_eaten = (
    time.get_seconds() / TIME_TO_EAT_PILE_SECONDS * FOOD_PER_PILE);
  if (amount_ > maximum_food_eaten)
  {
    food_eaten = maximum_food_eaten;
  }
  else
  {
    controller_->remove_pile(this);
    world_->deregister_world_object(this);
    food_eaten = amount_;
  }
  amount_ -= food_eaten;
  return Energy(amount_ * ENERGY_PER_FOOD);
}

FoodController::FoodController(World *world, WorldPlane *plane,
  const AbsoluteTime &time)
  : world_(world), plane_(plane), last_food_spawn_time_(time)
{
}

const AbsoluteTime FoodController::get_next_event_time()
{
  if (food_piles_.size() < MAX_FOOD_PILES_COUNT) {
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
    && food_piles_.size() < MAX_FOOD_PILES_COUNT)
  {
    last_food_spawn_time_ = time;
    FoodPile * food = new FoodPile(world_, this);
    while(true)
    {
      Coordinates coordinates = plane_->get_random_position();
      LOG(coordinates);
      try
      {
        world_->register_world_object(food, coordinates, UnitVector::from_degrees(0));
        food_piles_.insert(food);
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
  return food_piles_;
}

void FoodController::remove_pile(FoodPile *food_pile)
{
  food_piles_.erase(food_pile);
}
