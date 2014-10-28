#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <set>

class World;
class WorldObjectsCollection;
class WorldObject;
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
    const AbsoluteTime get_next_event_time() const;
};

#endif
