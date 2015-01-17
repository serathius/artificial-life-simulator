#include <cassert>

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

bool Vector::operator==(const Vector& other) const
{
    return x_ == other.x_ and y_ == other.y_;
}

UnitVector::UnitVector(float angle) : angle_(angle)
{
    
}

bool UnitVector::operator==(const UnitVector& other) const
{
    return angle_ == other.angle_;
}

float Coordinates::get_x()
{
    return x_;
}


float Coordinates::get_y()
{
    return y_;
}


float UnitVector::get_angle()
{
    return angle_;
}

float Dimension::get_x()
{
    return x_;
}


float Dimension::get_y()
{
    return y_;
}

Dimension::Dimension(float x, float y) : x_(x), y_(y)
{

}
