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
  std::vector<std::shared_ptr<WorldObject>> allocated_objects_;

  bool has_free_space(WorldObject*, const Coordinates&, const UnitVector&);

public:
  World(Model* const);
  void add_world_object(WorldObject*, const Coordinates&, const UnitVector&);
  void add_event_object(EventObject*);
  void update(const AbsoluteTime&);
  const AbsoluteTime get_next_event_time() const;
  const std::vector<std::shared_ptr<WorldObjectView>> get_objects() const;
  void move_object_forward(WorldObject*, const Distance&);
  void rotate_object(WorldObject*, const UnitVector&);
};

#endif
