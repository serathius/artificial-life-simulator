#include <cassert>

#include "model/coodinates_system.h"

CoordinatesSystem::CoordinatesSystem()
{
    
}

const Coordinates& CoordinatesSystem::get_coordinates(float, float) const
{
    
}

Coordinates::Coordinates(float x, float y, const CoordinatesSystem* const system)
    : x(x), y(y), system(system)
{
    
}

const Vector Coordinates::operator*(const UnitVector& unit_vector) const
{
    return Vector(this->x * unit_vector.x, this->y * unit_vector.y);
}

const DistanceVector Coordinates::operator-(const Coordinates& other) const
{
    assert(this->system == other.system);
    return DistanceVector(this->x - other.x, this->y - other.y);
}

const Coordinates Coordinates::operator+(const DistanceVector& vector) const
{
    return Coordinates(this->x + vector.x, this->y + vector.y, this->system);
}

const Coordinates Coordinates::operator-(const DistanceVector& vector) const
{
    return Coordinates(this->x - vector.x, this->y - vector.y, this->system);
}

bool Coordinates::operator==(const Coordinates& other) const
{
    return this->x == other.x and this->y == other.y;
}

Vector::Vector(float x, float y) : x(x), y(y)
{
    
}

DistanceVector::DistanceVector(float x, float y) : Vector(x, y)
{
    
}

const Coordinates DistanceVector::operator+(
    const Coordinates& coordinates) const
{
    return Coordinates(this->x + coordinates.x, this->y + coordinates.y, 
        coordinates.system);
}

const DistanceVector DistanceVector::operator+(
    const DistanceVector& other) const
{
    return DistanceVector(this->x + other.x, this->y + other.y);
}

const DistanceVector DistanceVector::operator-(
    const DistanceVector& other) const
{
    return DistanceVector(this->x - other.x, this->y - other.y);
}

bool DistanceVector::operator==(const DistanceVector& other) const
{
    return this->x == other.x and this->y == other.y;
}

UnitVector::UnitVector(float x, float y) : Vector(x, y)
{
    
}

UnitVector::UnitVector(const Vector& other) : UnitVector(other.x, other.y) 
{

}

bool UnitVector::operator==(const UnitVector& other) const
{
    return this->x == other.x and this->y == other.y;
}
