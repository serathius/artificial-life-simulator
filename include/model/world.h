#ifndef WORLD_H
#define WORLD_H

#include <memory>

class World;

#include "model.h"
#include "collections.h"

class World
{
private:
    WorldObjectsCollection objects_;

public:
    World(Model* const);
    const AbsoluteTime get_next_event_time() const;
    const std::vector<std::shared_ptr<WorldObjectView>> get_objects() const;
};

#endif
