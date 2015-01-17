#ifndef ORGANISM_H
#define ORGANISM_H

#include <memory>

#include "world.h"
#include "genotype.h"
#include "decision.h"
#include "primitives.h"


class OrganismCondition
{
};

class OrganismLogic
{
};

class OrganismUnderstoodWorldInformation
{
};

class Organism : public WorldObject, public EventObject
{
private:
    Coordinates coordinates_;
    UnitVector direction_;
    OrganismCondition condition_;
    const Genotype genotype_;
    const OrganismLogic logic_;

public:
    Organism(World * const world, const Coordinates& coordinates, const UnitVector& direction);
    const AbsoluteTime get_next_event_time();
    void update(const AbsoluteTime&);
    void draw();
};




#endif
