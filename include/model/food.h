#ifndef FOOD_H_
#define FOOD_H_

class FoodController;

#include "objects.h"
#include "organism.h"

typedef float FoodAmount;

class FoodPile : public WorldObject
{
public:
  FoodPile(World* const, FoodController*);
  virtual WorldObjectViewCollection get_view(const Coordinates&, const UnitVector&);
  virtual std::shared_ptr<Shape> get_shape(const Coordinates&, const UnitVector&);
  const Energy eat(const TimeDifference&);

private:
  const Distance get_radius();

  static constexpr FoodAmount FOOD_PER_PILE = 100;
  static constexpr float RADIUS_PER_FOOD = 0.001;
  static constexpr float TIME_TO_EAT_PILE_SECONDS = 0.5;
  static constexpr Energy ENERGY_PER_FOOD = 2.5;
  FoodAmount amount_;
  FoodController *controller_;
};

typedef std::set<FoodPile*> FoodCollection;

class FoodController : public EventObject
{
public:
  FoodController(World*, WorldPlane*, const AbsoluteTime&);
  const AbsoluteTime get_next_event_time();
  void update(const AbsoluteTime&);
  const FoodCollection& get_foods() const;
  void remove_pile(FoodPile*);

private:
  static constexpr float SPAWN_COOLDOWN_SECONDS = 5.f;
  static constexpr int MAX_FOOD_PILES_COUNT = 3;
  FoodCollection food_piles_;
  World* world_;
  WorldPlane* plane_;
  AbsoluteTime last_food_spawn_time_;
};
#endif /* FOOD_H_ */
