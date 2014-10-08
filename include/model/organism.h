#ifndef ORGANISM_H
#define ORGANISM_H

#include "world.h"

class Organism
{
    OrganismBody body;
    Genotype * const genotype;
    Logic * const logic;
    State * const state;

};

class OrganismBody: public DynamicWorldObject
{
};

class Genotype
{
public:

};

class Logic
{
public:
    Logic(const Genotype*);
    Decision* makeDecision(const State*, const SimpleWorldMockup*);

};

class State
{
private:
    float energy;
};

#endif