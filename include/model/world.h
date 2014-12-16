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
    World* const world_;
    Coordinates coordiantes_;
    UnitVector direction_;

public:
    WorldObject(World* const, const Coordinates&, const UnitVector&);
};


class WorldObjectsCollection
{
private:
    std::set<std::unique_ptr<WorldObject>> objects_;

public:
    ObjectCollectionIterator begin();
    ObjectCollectionIterator end();
    void add(WorldObject*);
    void remove(WorldObject*);
};


class World
{
private:
    Model* const model_;
    const CoordinatesSystem coordinates_system_;
    WorldObjectsCollection objects_;

public:
    World(Model* const);
    const AbsoluteTime get_next_event_time() const;
};

#endif
