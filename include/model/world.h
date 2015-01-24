#ifndef WORLD_H
#define WORLD_H

#include <memory>

class World;

#include "model.h"
#include "collections.h"

class World
{
private:
  WorldObjectsCollection world_objects_;
  EventObjectCollection event_objects_;

public:
  World(Model* const);
  void update(const AbsoluteTime&);
  const AbsoluteTime get_next_event_time() const;
  const std::vector<std::shared_ptr<WorldObjectView>> get_objects() const;
};

#endif
