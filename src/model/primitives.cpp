#include <cassert>
#include <math.h>

#include "model/primitives.h"


Coordinates::Coordinates(float x, float y)
    : x_(x), y_(y)
{
    
}

const Vector Coordinates::operator-(const Coordinates& other) const
{
    return Vector(x_ - other.x_, y_ - other.y_);
}

const Coordinates Coordinates::operator+(const Vector& vector) const
{
    return Coordinates(x_ + vector.x_, y_ + vector.y_);
}

const Coordinates Coordinates::operator-(const Vector& vector) const
{
    return Coordinates(x_ - vector.x_, y_ - vector.y_);
}

bool Coordinates::operator==(const Coordinates& other) const
{
    return x_ == other.x_ and y_ == other.y_;
}

const Distance Coordinates::distance(Coordinates const &other) const
{
    return (*this - other).length();
}

Vector::Vector(float x, float y) : x_(x), y_(y)
{
    
}

const Coordinates Vector::operator+(
    const Coordinates& coordinates) const
{
    return Coordinates(x_ + coordinates.x_, y_ + coordinates.y_);
}

const Vector Vector::operator+(
    const Vector& other) const
{
    return Vector(x_ + other.x_, y_ + other.y_);
}

const Vector Vector::operator-(
    const Vector& other) const
{
    return Vector(x_ - other.x_, y_ - other.y_);
}

const Distance Vector::length() const
{
    return Distance(sqrtf(x_ * x_ + y_ * y_));
}

bool Vector::operator==(const Vector& other) const
{
    return x_ == other.x_ and y_ == other.y_;
}

UnitVector::UnitVector(float angle) : angle_(angle)
{
    
}

UnitVector& UnitVector::operator=(const UnitVector& other)
{
    angle_ = other.angle_;
    return *this;
}

bool UnitVector::operator==(const UnitVector& other) const
{
    return angle_ == other.angle_;
}

const UnitVector UnitVector::operator+(const UnitVector& other) const
{
    return UnitVector(angle_ + other.angle_);
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
    return angle_;
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

const Distance Distance::operator+(const Distance& other) const
{
    return Distance(distance_ + other.distance_);
}

bool Distance::operator<(const Distance& other) const
{
    return distance_ < other.distance_;
}

std::ostream& operator<<(std::ostream& os, const Distance& distance)
{
    os << "Distance(" << distance.distance_ << ")";
    return os;
}
