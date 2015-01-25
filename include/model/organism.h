#ifndef ORGANISM_H
#define ORGANISM_H

#include <memory>

typedef float Energy;
typedef float Power;

#include "world.h"
#include "genotype.h"
#include "decision.h"
#include "primitives.h"
#include "logic.h"
#include "intersection.h"


class OrganismCondition
{
private:
  AbsoluteTime time_;
  Energy energy_;
  static constexpr Power ENERGY_LOSS_PER_SECOND = 50;

public:
  OrganismCondition(const AbsoluteTime&, const Energy&);
  const AbsoluteTime get_energy_runout_time() const;
  bool has_energy_left(const AbsoluteTime&) const;
  void add_energy(const Energy&);
};

class OrganismUnderstoodWorldInformation
{
};

class Organism : public WorldObject, public EventObject
{
public:
  Organism(World* const, const AbsoluteTime&);
  virtual ~Organism();
  static constexpr float ORGANISM_SIZE = 0.075;
  static constexpr float DECISION_COOLDOWN_SECODSN = 0.1;
  static constexpr float MAXIMUM_ROTATION_ANGLE = 20;
  static constexpr float MAXIMIM_DISTANCE_PER_UPDATE = 0.01;
  const AbsoluteTime get_next_event_time();
  void update(const AbsoluteTime&);
  virtual WorldObjectViewCollection get_view(const Coordinates&, const UnitVector&);
  virtual std::shared_ptr<Shape> get_shape(const Coordinates&, const UnitVector&);

private:
  void move_forward_food();
  void move_to_relative_position(const FoodRelativePosition&);

  OrganismCondition condition_;
  AbsoluteTime last_decision_time_;
  const Genotype genotype_;
  const OrganismLogic logic_;
};

#endif /* ORGANISM_H */
