#ifndef ORGANISM_H
#define ORGANISM_H

#include "world.h"


class Organism
{
    OrganismBody body;
    OrganismCondition condition;
    const Genotype genotype;
    const OrganismLogic logic;
};


class OrganismBody: public WorldObject, public EventObject
{
};


class OrganismLogic
{
public:
    explicit Logic(const Genotype&);
    Decision* const makeDecision(const OrganismCondition&, const tuple<OrganismUnderstoodWorldInformation>&);

};


class OrganismCondition
{
};


class OrganismUnderstoodWorldInformation
{

};

#endif
