#include "objects.h"

#ifndef FOOD_H_
#define FOOD_H_

typedef float FoodAmount;

class Food : public WorldObject
{
public:
  Food(World* const, const FoodAmount&);
  virtual std::shared_ptr<WorldObjectView> get_view(const Coordinates&, const UnitVector&);
  virtual std::shared_ptr<Shape> get_shape(const Coordinates&, const UnitVector&);

private:
  const Distance get_radius();

  FoodAmount amount_;
};


class FoodController : public EventObject
{
public:
  FoodController(World*, WorldPlane*, const AbsoluteTime&);
  const AbsoluteTime get_next_event_time();
  void update(const AbsoluteTime&);

private:
  static constexpr float SPAWN_COOLDOWN_SECONDS = 5.f;
  static constexpr int MAX_FOOD_PILES_COUNT = 3;
  std::vector<Food*> foods_;
  World* world_;
  WorldPlane* plane_;
  AbsoluteTime last_food_spawn_time_;
};
#endif /* FOOD_H_ */
