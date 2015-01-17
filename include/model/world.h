#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <set>

class World;
class WorldObjectsCollection;
class WorldObject;


#include "model.h"
#include "primitives.h"


class WorldObject
{
private:
    World* const world_;

public:
    WorldObject(World* const);
    virtual void draw() = 0;
};


class WorldPlane : public WorldObject
{
private:
    Dimension dimension_;

public:
    WorldPlane(World* const, const Dimension&);
    virtual void draw();
};

class WorldObjectsCollection
{
private:
    std::set<std::shared_ptr<WorldObject>> objects_;

public:
    typedef std::set<std::shared_ptr<WorldObject>>::iterator iterator;
    iterator begin() const;
    iterator end() const;
    void add(WorldObject*);
    void remove(WorldObject*);
};


class World
{
private:
    Model* const model_;
    WorldObjectsCollection objects_;

public:
    World(Model* const);
    const AbsoluteTime get_next_event_time() const;
    const std::vector<WorldObject*> get_objects() const;
};

#endif
