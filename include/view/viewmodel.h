#ifndef VIEWMODEL_H_
#define VIEWMODEL_H_

#include <vector>

class WorldObjectView;

#include "model/world.h"
#include "model/primitives.h"
#include "common.h"

class WorldObjectView
{
public:
  virtual ~WorldObjectView(){;}
  virtual void draw() = 0;
};

class TriangleWorldObjectView : public WorldObjectView
{
private:
  const Coordinates coordinates_;
  const UnitVector direction_;

public:
  TriangleWorldObjectView(const Coordinates& coordinates,
    const UnitVector& direction);
  virtual ~TriangleWorldObjectView(){;}
  virtual void draw();
};

class ViewModel
{
private:
  std::vector<std::shared_ptr<WorldObjectView>> objects_;

public:
  ViewModel(){};
  ViewModel(const std::vector<std::shared_ptr<WorldObjectView>>& objects);
  void draw();
};

class SquareWorldObjectView : public WorldObjectView
{
private:
  const Coordinates coordinates_;
  const UnitVector direction_;
  const Dimension dimension_;

public:
  SquareWorldObjectView(const Coordinates& coordinates,
    const UnitVector& direction, const Dimension& dimension);
  virtual ~SquareWorldObjectView(){;}
  virtual void draw();
};

#endif /* VIEWMODEL_H_ */
