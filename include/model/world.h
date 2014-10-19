#include <memory>

#ifndef WORLD_H
#define WORLD_H

class World
{
private:
    Model* const Model model;
    const CoordinatesSystem coordinates_system;
    ObjectsCollection objects;

public:
    World(Model* const);
    void update(const AbsoluteTime&);
    const AbsoluteTime get_next_event_time() const;
    void register(WorldObject* const);
};


class ObjectsCollection
{
private:
    std::vector<std::unique_ptr<Object>> objects;

public:
    ObjectsCollection();
    ~ObjectsCollection();
    typedef std::vector<std::unique_ptr<Object>>::iterator
        ObjectCollectionIterator;
    ObjectsCollectionIterator& begin();
    ObjectsCollectionIterator& iterator end();
    void add(WorldObject*);
    void remove(WorldObject*);
};


class WorldObject : public ModelObject
{
private:
    World* const world;
    Coordinates coordiantes;
    UnitVector direction;

public:
    WorldObject(World* const, const Coordinates&, const UnitVector&)
};

#endif
