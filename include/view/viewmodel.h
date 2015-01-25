#ifndef VIEWMODEL_H_
#define VIEWMODEL_H_

#include <vector>
#include <memory>

class WorldObjectView;
typedef std::vector<std::shared_ptr<WorldObjectView>> WorldObjectViewCollection;

#include "model/primitives.h"
#include "common.h"

struct Color
{
  float R;
  float G;
  float B;
};

class WorldObjectView
{
public:
  virtual ~WorldObjectView(){;}
  virtual void draw() = 0;
  virtual float get_z(){return 0;};
};

class ViewModel
{
private:
  WorldObjectViewCollection objects_;

public:
  ViewModel(){};
  ViewModel(const WorldObjectViewCollection& objects);
  void draw();
};

class TriangleWorldObjectView : public WorldObjectView
{
private:
  const Coordinates coordinates_;
  const UnitVector direction_;
  const float z_;
  const Color color_;

public:
  TriangleWorldObjectView(const Coordinates& coordinates,
    const UnitVector& direction, float z, const Color&);
  virtual ~TriangleWorldObjectView(){;}
  virtual void draw();
  float get_z(){return z_;};
};

class SquareWorldObjectView : public WorldObjectView
{
private:
  const Coordinates coordinates_;
  const UnitVector direction_;
  const Dimension dimension_;
  const float z_;
  const Color color_;

public:
  SquareWorldObjectView(const Coordinates& coordinates,
    const UnitVector& direction, const Dimension& dimension, float z,
    const Color&);
  virtual ~SquareWorldObjectView(){;}
  virtual void draw();
  float get_z(){return z_;};
};

class CircleWorldObjectView : public WorldObjectView
{
private:
  const Coordinates coordinates_;
  const Distance distance_;
  const float z_;
  const Color color_;
  static const int SEGMENTS_COUNT = 32;

public:
  CircleWorldObjectView(const Coordinates& coordinates,
    const Distance& distance, float z, const Color&);
  virtual ~CircleWorldObjectView(){;}
  virtual void draw();
  float get_z(){return z_;};
};

#endif /* VIEWMODEL_H_ */
