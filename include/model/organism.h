#ifndef ORGANISM_H
#define ORGANISM_H

#include "world.h"
#include "decision.h"


class Organism
{
private:
    OrganismBody body;
    OrganismCondition condition;
    const Genotype genotype;
    const OrganismLogic logic;
    void do_decision(const Decision* const);
};


class OrganismBody: public WorldObject, public EventObject
{
};


class OrganismLogic
{
public:
    explicit Logic(const Genotype&);
    const Decision* const makeDecision(const OrganismCondition&,
        const tuple<OrganismUnderstoodWorldInformation>&);

};


class OrganismCondition
{
};


class OrganismUnderstoodWorldInformation
{

};

#endif
