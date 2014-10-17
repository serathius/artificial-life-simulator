#ifndef ORGANISM_H
#define ORGANISM_H

#include <memory>

#include "world.h"


class Organism
{
    OrganismBody body;
    OrganismCondition condition;
    const OrganismGenotype genotype;
    const OrganismLogic logic;

};


class OrganismBody: public WorldObject, public EventObject
{
    void realise(const std::unique_ptr<const Decision>);
};


class OrganismGenotype
{
};


class OrganismLogic
{
private:
    AbsoluteTime last_decision_time;

public:
    explicit Logic(const Genotype&);
    const std::unique_ptr<const Decision> make_decision(const OrganismCondition&,
        const tuple<OrganismUnderstoodWorldInformation>&);

};


class OrganismCondition
{
};


class OrganismUnderstoodWorldInformation
{

};

#endif
