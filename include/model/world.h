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
    void add(Object*);
    void remove(Object*);
};

class Object
{
private:
    World* const world;
    Coordinates* coordiantes;
    UnitVector* direction;
};

class PhysicalObject : private Object
{
private:
    Velocity* velocity;
};

class Velocity : public Vector
{

};

#endif