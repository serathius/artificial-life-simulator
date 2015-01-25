#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <random>

class World;

#include "model.h"
#include "collections.h"
#include "food.h"

struct FoodRelativePosition
{
  Food* food;
  UnitVector direction;
  Distance distance;
};


class World
{
private:
  WorldObjectsCollection world_objects_;
  EventObjectCollection event_objects_;
  std::set<Object*> allocated_objects_;
  FoodController* food_controller_;

  bool has_free_space(WorldObject*, const Coordinates&, const UnitVector&);

public:
  World(Model* const);
  ~World();
  void register_world_object(WorldObject*, const Coordinates &, const UnitVector &);
  void register_event_object(EventObject*);
  void deregister_world_object(WorldObject*);
  void deregister_event_object(EventObject*);
  void update(const AbsoluteTime&);
  const AbsoluteTime get_next_event_time() const;
  const std::vector<std::shared_ptr<ViewElement>> get_objects() const;
  void move_object_forward(WorldObject*, const Distance&);
  void rotate_object(WorldObject*, const UnitVector&);
  std::vector<FoodRelativePosition> get_relative_foods_position(
    WorldObject*) const;

  std::default_random_engine random_generator_engine_;
};

class NoSpace : public std::exception
{

};

#endif
