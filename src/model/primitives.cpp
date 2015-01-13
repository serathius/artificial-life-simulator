#include <cassert>

#include "model/primitives.h"


Coordinates::Coordinates(float x, float y)
    : x_(x), y_(y)
{
    
}

const Vector Coordinates::operator*(const UnitVector& unit_vector) const
{
    return Vector(x_ * unit_vector.x_, y_ * unit_vector.y_);
}

const DistanceVector Coordinates::operator-(const Coordinates& other) const
{
    return DistanceVector(x_ - other.x_, y_ - other.y_);
}

const Coordinates Coordinates::operator+(const DistanceVector& vector) const
{
    return Coordinates(x_ + vector.x_, y_ + vector.y_);
}

const Coordinates Coordinates::operator-(const DistanceVector& vector) const
{
    return Coordinates(x_ - vector.x_, y_ - vector.y_);
}

bool Coordinates::operator==(const Coordinates& other) const
{
    return x_ == other.x_ and y_ == other.y_;
}

Vector::Vector(float x, float y) : x_(x), y_(y)
{
    
}

DistanceVector::DistanceVector(float x, float y) : Vector(x, y)
{
    
}

const Coordinates DistanceVector::operator+(
    const Coordinates& coordinates) const
{
    return Coordinates(x_ + coordinates.x_, y_ + coordinates.y_);
}

const DistanceVector DistanceVector::operator+(
    const DistanceVector& other) const
{
    return DistanceVector(x_ + other.x_, y_ + other.y_);
}

const DistanceVector DistanceVector::operator-(
    const DistanceVector& other) const
{
    return DistanceVector(x_ - other.x_, y_ - other.y_);
}

bool DistanceVector::operator==(const DistanceVector& other) const
{
    return x_ == other.x_ and y_ == other.y_;
}

UnitVector::UnitVector(float x, float y) : Vector(x, y)
{
    
}

UnitVector::UnitVector(const Vector& other) : UnitVector(other.x_, other.y_)
{

}

bool UnitVector::operator==(const UnitVector& other) const
{
    return x_ == other.x_ and y_ == other.y_;
}
