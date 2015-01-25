#ifndef VIEWMODEL_H_
#define VIEWMODEL_H_

#include <vector>
#include <memory>

class ViewElement;
typedef std::vector<std::shared_ptr<ViewElement>> WorldObjectViewCollection;

#include "model/primitives.h"
#include "common.h"

struct Color
{
  float R;
  float G;
  float B;
};

class ViewElement
{
public:
  virtual ~ViewElement(){;}
  virtual void draw() = 0;
  virtual float get_z() = 0;
};

class ViewModel
{
private:
  WorldObjectViewCollection objects_;

public:
  ViewModel();
  ViewModel(const WorldObjectViewCollection& objects);
  void draw();
};

class TriangleViewElement : public ViewElement
{
private:
  const Coordinates coordinates_;
  const UnitVector direction_;
  const float z_;
  const Color color_;
  const Distance length_of_side_;

public:
  TriangleViewElement(const Coordinates& coordinates,
    const UnitVector& direction, float z, const Color&,
    const Distance&);
  virtual ~TriangleViewElement(){;}
  virtual void draw();
  float get_z(){return z_;};
};

class RectangleViewElement : public ViewElement
{
private:
  const Coordinates coordinates_;
  const UnitVector direction_;
  const Dimension dimension_;
  const float z_;
  const Color color_;

public:
  RectangleViewElement(const Coordinates& coordinates,
    const UnitVector& direction, const Dimension& dimension, float z,
    const Color&);
  virtual ~RectangleViewElement(){;}
  virtual void draw();
  float get_z(){return z_;};
};

class CircleViewElement : public ViewElement
{
private:
  const Coordinates coordinates_;
  const Distance distance_;
  const float z_;
  const Color color_;
  static const int SEGMENTS_COUNT = 32;

public:
  CircleViewElement(const Coordinates& coordinates,
    const Distance& distance, float z, const Color&);
  virtual ~CircleViewElement(){;}
  virtual void draw();
  float get_z(){return z_;};
};

#endif /* VIEWMODEL_H_ */
