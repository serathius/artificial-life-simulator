#include <algorithm>

#include "model/organism.h"

OrganismCondition::OrganismCondition(
  const AbsoluteTime &time, const Energy &energy)
  : time_(time), energy_(energy)
{
}

const AbsoluteTime OrganismCondition::get_energy_runout_time() const
{
  return time_ + TimeDifference::seconds(energy_ / ENERGY_LOSS);
}

bool OrganismCondition::has_energy_left(const AbsoluteTime &time) const
{
  return energy_ - (time - time_).get_seconds() * ENERGY_LOSS > 0;
}

Organism::Organism(World * const world, const AbsoluteTime &time)
  : WorldObject(world), condition_(OrganismCondition(time, 1000)),
    last_decision_time_(time), genotype_(Genotype()), logic_(OrganismLogic())
{

}

Organism::~Organism()
{

}

bool nearest_food_comparator(const FoodRelativePosition &first,
  const FoodRelativePosition &second)
{
  return first.distance < second.distance;
}

void Organism::update(const AbsoluteTime &time)
{
  if(!condition_.has_energy_left(time))
  {
    world_->deregister_world_object(this);
    world_->deregister_event_object(this);
    LOG("Organism died");
  }
  else
  {
    if (time >= last_decision_time_ + TimeDifference::seconds(0.25))
    {
      auto foods = world_->get_relative_foods_position(this);
      if (foods.begin() != foods.end())
      {
        sort(foods.begin(), foods.end(), nearest_food_comparator);
        FoodRelativePosition nearest_food_pair = foods[0];
        LOG(nearest_food_pair.direction);
        if (nearest_food_pair.direction == UnitVector::from_degrees(0))
        {
          world_->move_object_forward(this, Distance(0.01));
        }
        else
        {
          world_->rotate_object(this, nearest_food_pair.direction);
        }
      }
      last_decision_time_ = time;
    }
  }
}

std::shared_ptr<WorldObjectView> Organism::get_view(const Coordinates &coordinates,
  const UnitVector &direction)
{
  return std::shared_ptr<WorldObjectView>(
    new TriangleWorldObjectView(coordinates, direction, 1, {1, 0, 0}));
}

std::shared_ptr<Shape> Organism::get_shape(const Coordinates &coordinates,
  const UnitVector &direction)
{
  return std::shared_ptr<Shape>(new Circle(coordinates, Distance(0.1)));
}

const AbsoluteTime Organism::get_next_event_time()
{
  auto decision_time = last_decision_time_ + TimeDifference::seconds(0.25);
  auto energy_runout_time = condition_.get_energy_runout_time();
  if (decision_time > energy_runout_time)
  {
    return energy_runout_time;
  }
  else
  {
    return decision_time;
  }
}
