#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <iostream>

class UnitVector;
class Vector;
class Distance;

class Coordinates
{
  friend class Vector;

public:
  Coordinates(float, float);
  bool operator==(const Coordinates&) const;
  friend std::ostream& operator<<(std::ostream&, const Coordinates&);
  const Vector operator*(const UnitVector&) const;
  const Vector operator-(const Coordinates&) const;
  const Coordinates operator+(const Vector&) const;
  Coordinates& operator+=(const Vector&);
  const Coordinates operator-(const Vector&) const;
  const Distance distance(const Coordinates&) const;
  float get_x() const;
  float get_y() const;

private:
  float x_;
  float y_;
};


class Dimension
{
public:
  Dimension(float x, float y);
  bool operator==(const Dimension &other) const;
  bool operator!=(const Dimension &other) const;
  const Coordinates operator+(const Coordinates &point) const;
  const Vector to_vector() const;
  float get_x() const;
  float get_y() const;

private:
  const float x_;
  const float y_;
};


class Vector
{
  friend class Coordinates;
  friend class UnitVector;

public:
  Vector(float, float);
  bool operator==(const Vector&) const;
  friend std::ostream& operator<<(std::ostream&, const Vector&);
  Vector& operator=(const Vector&);
  const Coordinates operator+(const Coordinates&) const;
  const Vector operator+(const Vector&) const;
  const Vector operator-(const Vector&) const;
  const Distance length() const;

private:
  float x_;
  float y_;
};


class UnitVector
{
  friend class Coordinates;

public:
  explicit UnitVector(const Vector&);
  bool operator==(const UnitVector&) const;
  bool operator<(const UnitVector&) const;
  bool operator<=(const UnitVector&) const;
  UnitVector& operator=(const UnitVector&);
  friend std::ostream& operator<<(std::ostream&, const UnitVector&);
  const UnitVector operator+(const UnitVector&) const;
  const UnitVector operator-(const UnitVector&) const;
  const Vector operator*(const Distance&) const;
  static const UnitVector from_degrees(float);
  const UnitVector absolute() const;
  float get_angle() const;

private:
  UnitVector(double);

  double radians_;
};


class Distance
{
public:
  Distance(float);
  bool operator==(const Distance&) const;
  bool operator<(const Distance&) const;
  bool operator<=(const Distance&) const;
  friend std::ostream& operator<<(std::ostream& os, const Distance& distance);
  const Distance operator+(const Distance&) const;
  const Distance operator-(const Distance&) const;
  float get_distance() const;

private:
  float distance_;
};
#endif /* PRIMITIVES_H */
