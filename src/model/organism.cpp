#include <algorithm>

#include "model/organism.h"

OrganismCondition::OrganismCondition(const AbsoluteTime &time)
  : time_(time), energy_(STARTING_ENERGY)
{
}

const AbsoluteTime OrganismCondition::get_energy_runout_time() const
{
  return time_ + TimeDifference::seconds(energy_ / ENERGY_LOSS_PER_SECOND);
}

Energy OrganismCondition::energy_left(const AbsoluteTime &time) const
{
  return energy_ - (time - time_).get_seconds() * ENERGY_LOSS_PER_SECOND;
}

void OrganismCondition::add_energy(const Energy &energy)
{
  energy_ += energy;
}

Organism::Organism(World * const world, OrganismRegister *organism_register,
  const AbsoluteTime &time)
  : WorldObject(world), condition_(OrganismCondition(time)),
    last_decision_time_(time), genotype_(Genotype()),
    register_(organism_register)
{

}

Organism::~Organism()
{

}

float Organism::movement_cost(const RelativePosition& position)
{
  return (position.direction.absolute().get_angle()
    / MAXIMUM_ROTATION_ANGLE + position.distance.get_distance()
    / MAXIMIM_DISTANCE_PER_UPDATE);
}


void Organism::update(const AbsoluteTime &time)
{
  if(condition_.energy_left(time) < 0)
  {
    register_->deregister(this);
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
    sort(foods.begin(), foods.end(), []
      (const FoodRelativePosition &first, const FoodRelativePosition &second) -> bool
      {
        return movement_cost(first.second) < movement_cost(second.second);
      });
    FoodPile* nearest_food = foods[0].first;
    RelativePosition nearest_food_position = foods[0].second;
    if (nearest_food_position.distance < Distance(MAXIMIM_DISTANCE_PER_UPDATE))
    {
      condition_.add_energy(nearest_food->eat(
        TimeDifference::seconds(DECISION_COOLDOWN_SECODSN)));
    }
    else
    {
      move_to_relative_position(nearest_food_position);
    }
  }
}

void Organism::move_to_relative_position(
  const RelativePosition& food_position)
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
    new Circle(coordinates, Distance(ORGANISM_SIZE * sqrtf(2) / 2)));
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

OrganismRegister::OrganismRegister(World *world) : world_(world)
{
  register_organism(new Organism(world_, this, AbsoluteTime(0)),
    Coordinates(-0.5f, 0), UnitVector::from_degrees(0));
  register_organism(new Organism(world_, this, AbsoluteTime(0)),
    Coordinates(0.5f, 0), UnitVector::from_degrees(180));
  register_organism(new Organism(world_, this, AbsoluteTime(0)),
    Coordinates(0, 0.5f), UnitVector::from_degrees(-90));
  register_organism(new Organism(world_, this, AbsoluteTime(0)),
    Coordinates(0, -0.5f), UnitVector::from_degrees(90));
}

void OrganismRegister::register_organism(
  Organism *organism, Coordinates const &coordinates, UnitVector const &direction)
{
  world_->register_world_object(organism, coordinates, direction);
  world_->register_event_object(organism);
  organisms_.insert(organism);
}

void OrganismRegister::deregister(Organism *organism)
{
  world_->deregister_world_object(organism);
  world_->deregister_event_object(organism);
  organisms_.erase(organism);
}
