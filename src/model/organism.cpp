#include <algorithm>

#include "model/organism.h"

OrganismCondition::OrganismCondition(
  const AbsoluteTime &time, const Energy &energy)
  : time_(time), energy_(energy)
{
}

const AbsoluteTime OrganismCondition::get_energy_runout_time() const
{
  return time_ + TimeDifference::seconds(energy_ / ENERGY_LOSS_PER_SECOND);
}

bool OrganismCondition::has_energy_left(const AbsoluteTime &time) const
{
  return energy_ - (time - time_).get_seconds() * ENERGY_LOSS_PER_SECOND > 0;
}

void OrganismCondition::add_energy(const Energy &energy)
{
  energy_ += energy;
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
    if (time >= last_decision_time_ + TimeDifference::seconds(
      DECISION_COOLDOWN_SECODSN))
    {
      move_forward_food();
      last_decision_time_ = time;
    }
  }
}

void Organism::move_forward_food()
{
  auto foods = world_->get_relative_foods_position(this);
  if (foods.begin() != foods.end())
  {
    sort(foods.begin(), foods.end(), nearest_food_comparator);
    FoodRelativePosition nearest_food_position = foods[0];
    if (nearest_food_position.distance < Distance(MAXIMIM_DISTANCE_PER_UPDATE))
    {
      condition_.add_energy(nearest_food_position.food->eat(
        TimeDifference::seconds(DECISION_COOLDOWN_SECODSN)));
    }
    else
    {
      move_to_relative_position(nearest_food_position);
    }
  }
}

void Organism::move_to_relative_position(
  const FoodRelativePosition& food_position)
{
  if (food_position.direction == UnitVector::from_degrees(0))
  {
    world_->move_object_forward(this, Distance(MAXIMIM_DISTANCE_PER_UPDATE));
  }
  else
  {
    if(food_position.direction.absolute()
      < UnitVector::from_degrees(MAXIMUM_ROTATION_ANGLE))
    {
      world_->rotate_object(this, food_position.direction);
    }
    else
    {
      if(food_position.direction < UnitVector::from_degrees(0))
      {
        world_->rotate_object(this, UnitVector::from_degrees(
          -MAXIMUM_ROTATION_ANGLE));
      }
      else
      {
        world_->rotate_object(this, UnitVector::from_degrees(
          MAXIMUM_ROTATION_ANGLE));
      }
    }
  }
}

WorldObjectViewCollection Organism::get_view(const Coordinates &coordinates,
  const UnitVector &direction)
{
  WorldObjectViewCollection world_object_view;
  world_object_view.push_back(std::shared_ptr<ViewElement>(
  new TriangleViewElement(
      coordinates, direction, 1, {1, 0, 0}, Distance(ORGANISM_SIZE * 2))));
  return world_object_view;
}

std::shared_ptr<Shape> Organism::get_shape(const Coordinates &coordinates,
  const UnitVector &direction)
{
  return std::shared_ptr<Shape>(
    new Circle(coordinates, Distance(ORGANISM_SIZE)));
}

const AbsoluteTime Organism::get_next_event_time()
{
  auto decision_time = last_decision_time_ + TimeDifference::seconds(
    DECISION_COOLDOWN_SECODSN);
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
