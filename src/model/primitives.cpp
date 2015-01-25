#include <cassert>
#include <cmath>
#include <limits>

#include "model/primitives.h"

bool almost_equal(float first, float second)
{
  return fabs(first - second) < std::numeric_limits<float>::epsilon();
}

bool almost_equal(double first, double second)
{
  return fabs(first - second) < std::numeric_limits<double>::epsilon();
}

Coordinates::Coordinates(float x, float y)
    : x_(x), y_(y)
{
    
}

std::ostream& operator<<(std::ostream &os, const Coordinates &coordinates)
{
  os << "Coordinates(" << coordinates.x_ << ", " << coordinates.y_ << ")";
  return os;
}

bool Coordinates::operator==(const Coordinates& other) const
{
    return almost_equal(x_, other.x_) and almost_equal(y_, other.y_);
}

const Vector Coordinates::operator-(const Coordinates &other) const
{
    return Vector(x_ - other.x_, y_ - other.y_);
}

const Coordinates Coordinates::operator+(const Vector& vector) const
{
    return Coordinates(x_ + vector.x_, y_ + vector.y_);
}

Coordinates& Coordinates::operator+=(const Vector& vector)
{
  x_ += vector.x_;
  y_ += vector.y_;
  return *this;
}

const Coordinates Coordinates::operator-(const Vector& vector) const
{
    return Coordinates(x_ - vector.x_, y_ - vector.y_);
}

const Distance Coordinates::distance(Coordinates const &other) const
{
    return (*this - other).length();
}

Vector::Vector(float x, float y) : x_(x), y_(y)
{
    
}

std::ostream& operator<<(std::ostream &os, const Vector &vector)
{
  os << "Vector(" << vector.x_ << ", " << vector.y_ << ")";
  return os;
}

Vector& Vector::operator=(const Vector &other)
{
  x_ = other.x_;
  y_ = other.y_;
  return *this;
}

const Coordinates Vector::operator+(
    const Coordinates &coordinates) const
{
    return Coordinates(x_ + coordinates.x_, y_ + coordinates.y_);
}

const Vector Vector::operator+(
    const Vector &other) const
{
    return Vector(x_ + other.x_, y_ + other.y_);
}

const Vector Vector::operator-(
    const Vector &other) const
{
    return Vector(x_ - other.x_, y_ - other.y_);
}

const Distance Vector::length() const
{
    return Distance(sqrtf(x_ * x_ + y_ * y_));
}

bool Vector::operator==(const Vector &other) const
{
  return almost_equal(x_, other.x_) and almost_equal(y_, other.y_);
}

const UnitVector UnitVector::from_degrees(float angle)
{
    return UnitVector(angle / 180 * M_PI);
}

std::ostream& operator<<(std::ostream &os, const UnitVector &direction)
{
  auto angle = direction.get_angle();
  os << "UnitVector(" << angle - int(angle / 360) << ")";
  return os;
}

UnitVector::UnitVector(double radians) : radians_(radians)
{
    
}

UnitVector::UnitVector(Vector const &vector)
  : radians_(atan2(vector.y_, vector.x_))
{

}

UnitVector& UnitVector::operator=(const UnitVector &other)
{
    radians_ = other.radians_;
    return *this;
}

bool UnitVector::operator<(const UnitVector &other) const
{
  return radians_ < other.radians_;
}

bool UnitVector::operator==(const UnitVector &other) const
{
    return almost_equal(radians_, other.radians_);
}

const UnitVector UnitVector::operator+(const UnitVector &other) const
{
    return UnitVector(radians_ + other.radians_);
}

const UnitVector UnitVector::operator-(const UnitVector &other) const
{
  return UnitVector(radians_ - other.radians_);
}

const Vector UnitVector::operator*(const Distance &distance) const
{
    return Vector(static_cast<float>(cos(radians_) * distance.get_distance()),
                  static_cast<float>(sin(radians_) * distance.get_distance()));
}

const UnitVector UnitVector::absolute() const
{
  return UnitVector(fabs(radians_));
}

float Coordinates::get_x() const
{
    return x_;
}

float Coordinates::get_y() const
{
    return y_;
}

float UnitVector::get_angle() const
{
    return static_cast<float>(radians_ * 180 / M_PI);
}

float Dimension::get_x() const
{
    return x_;
}

float Dimension::get_y() const
{
    return y_;
}

Dimension::Dimension(float x, float y) : x_(x), y_(y)
{
  assert(x > 0);
  assert(y > 0);
}

Distance::Distance(float distance) : distance_(distance)
{

}

const Distance Distance::operator+(const Distance &other) const
{
    return Distance(distance_ + other.distance_);
}

const Distance Distance::operator-(const Distance &other) const
{
    return Distance(distance_ - other.distance_);
}


bool Distance::operator<(const Distance &other) const
{
    return distance_ < other.distance_;
}

bool Distance::operator<=(const Distance &other) const
{
    return distance_ <= other.distance_;
}

float Distance::get_distance() const
{
    return distance_;
}

std::ostream& operator<<(std::ostream &os, const Distance &distance)
{
    os << "Distance(" << distance.distance_ << ")";
    return os;
}
