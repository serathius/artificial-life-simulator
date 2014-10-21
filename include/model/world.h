#ifndef WORLD_H
#define WORLD_H

class World;
class WorldObjectsCollection;
class WorldObject;


#include <memory>
#include <set>

typedef std::set<std::unique_ptr<WorldObject>>::iterator
    ObjectCollectionIterator;

#include "model.h"
#include "coodinates_system.h"


class WorldObject : public ModelObject
{
private:
    World* const world;
    Coordinates coordiantes;
    UnitVector direction;

public:
    WorldObject(World* const, const Coordinates&, const UnitVector&);
};


class WorldObjectsCollection
{
private:
    std::set<std::unique_ptr<WorldObject>> objects;

public:
    ObjectCollectionIterator begin();
    ObjectCollectionIterator end();
    void add(WorldObject*);
    void remove(WorldObject*);
};


class World
{
private:
    Model* const model;
    const CoordinatesSystem coordinates_system;
    WorldObjectsCollection objects;

public:
    World(Model* const);
    void update(const AbsoluteTime&);
    const AbsoluteTime get_next_event_time() const;
};

#endif
