#ifndef ORGANISM_H
#define ORGANISM_H

#include <memory>
#include <set>

typedef float Energy;
typedef float Power;
class World;
class Organism;

#include "primitives.h"

class OrganismRegister
{
public:
  OrganismRegister(World*);
  void deregister(Organism*);

private:
  void register_organism(Organism*, const Coordinates&, const UnitVector&);

  World* world_;
  std::set<Organism*> organisms_;

};

#include "world.h"
#include "genotype.h"
#include "decision.h"
#include "intersection.h"


class OrganismCondition
{
public:
  OrganismCondition(const AbsoluteTime&);
  const AbsoluteTime get_energy_runout_time() const;
  bool has_energy_left(const AbsoluteTime&) const;
  void add_energy(const Energy&);

private:
  static constexpr Power ENERGY_LOSS_PER_SECOND = 35;
  static constexpr Energy STARTING_ENERGY = 1000;

  AbsoluteTime time_;
  Energy energy_;
};

class OrganismUnderstoodWorldInformation
{
};

class Organism : public WorldObject, public EventObject
{
public:
  Organism(World* const, OrganismRegister*, const AbsoluteTime&);
  virtual ~Organism();
  static constexpr float ORGANISM_SIZE = 0.075;
  static constexpr float DECISION_COOLDOWN_SECODSN = 0.1;
  static constexpr float MAXIMUM_ROTATION_ANGLE = 30;
  static constexpr float MAXIMIM_DISTANCE_PER_UPDATE = 0.01;
  const AbsoluteTime get_next_event_time();
  void update(const AbsoluteTime&);
  virtual WorldObjectViewCollection get_view(const Coordinates&,
    const UnitVector&);
  virtual std::shared_ptr<Shape> get_shape(const Coordinates&,
    const UnitVector&);

private:
  void move_forward_food();
  void move_to_relative_position(const RelativePosition&);
  static float movement_cost(const RelativePosition&);

  OrganismCondition condition_;
  AbsoluteTime last_decision_time_;
  const Genotype genotype_;
  OrganismRegister* register_;
};

#endif /* ORGANISM_H */
