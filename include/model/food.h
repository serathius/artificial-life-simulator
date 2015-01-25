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

#endif /* FOOD_H_ */
