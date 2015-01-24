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

void Organism::update(const AbsoluteTime &time)
{
  if(!condition_.has_energy_left(time))
  {
    world_->remove_world_object(this);
    world_->remove_event_object(this);
    LOG("Organism died");
  }
  else
  {
    if (time >= last_decision_time_ + TimeDifference::seconds(1)) {
      world_->move_object_forward(this, Distance(0.01));
      last_decision_time_ = time;
    }
  }
}

std::shared_ptr<WorldObjectView> Organism::get_view(const Coordinates &coordinates,
  const UnitVector &direction)
{
  return std::shared_ptr<WorldObjectView>(
    new TriangleWorldObjectView(coordinates, direction));
}

std::shared_ptr<Shape> Organism::get_shape(const Coordinates &coordinates,
  const UnitVector &direction)
{
  return std::shared_ptr<Shape>(new Circle(coordinates, Distance(0.1)));
}

const AbsoluteTime Organism::get_next_event_time()
{
  auto decision_time = last_decision_time_ + TimeDifference::seconds(1);
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
