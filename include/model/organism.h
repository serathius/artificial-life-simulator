#ifndef ORGANISM_H
#define ORGANISM_H

#include <memory>

#include "world.h"
#include "genotype.h"
#include "decision.h"
#include "primitives.h"
#include "logic.h"

class OrganismCondition
{
};

class OrganismUnderstoodWorldInformation
{
};

class Organism : public WorldObject, public EventObject
{
public:
  Organism(World* const, const AbsoluteTime&);
  virtual ~Organism();
  const AbsoluteTime get_next_event_time();
  void update(const AbsoluteTime&);
  virtual WorldObjectView* get_view(const Coordinates&, const UnitVector&);

private:
  OrganismCondition condition_;
  AbsoluteTime last_decision_time_;
  const Genotype genotype_;
  const OrganismLogic logic_;
};

#endif /* ORGANISM_H */
