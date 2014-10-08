#include <memory>

#ifndef WORLD_H
#define WORLD_H

class World
{
private:
    CoordinatesSystem coordinates_system;
    ObjectsCollection objects;

public:
    World();
    tuple<std::PhysicalObject*> get_objects() const;
    SimpleWorldMockup* getOrganismWorldMockup(Organism* organism);
};

class ObjectsCollection
{
private:
    vector<std::unique_ptr<Object>> objects;

public:
    ObjectsCollection();
    ~ObjectsCollection();
    class ObjectsCollectionIterator
    {
    private:
        ObjectsCollection* const collection;
    public:
        Object* operator++();
    };
    ObjectsCollectionIterator& begin();
    ObjectsCollectionIterator& iterator end();
    void add(WorldObject*);
    void remove(WorldObject*);
};

class WorldObject
{
private:
    World* const world;
    Coordinates* coordiantes;
};

class DynamicWorldObject : private WorldObject
{
private:
    Velocity* velocity;
    UnitVector* direction;
};

class Velocity : public Vector
{

};

#endif