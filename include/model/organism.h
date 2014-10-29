#ifndef ORGANISM_H
#define ORGANISM_H

#include <memory>
#include <functional>

#include "world.h"
#include "genotype.h"
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
	unique_ptr <std::function> draw;
    void realise(const std::unique_ptr<const Decision>);
    void update(const AbsoluteTime&);
    OrganismBody(std::function);
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
