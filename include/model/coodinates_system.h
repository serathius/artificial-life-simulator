#ifndef COORDINATES_SYSTEM_H
#define COORDINATES_SYSTEM_H

class Coordinates;
class DistanceVector;
class UnitVector;
class Vector;


class CoordinatesSystem
{
public:
    CoordinatesSystem();
    const Coordinates& get_coordinates(float, float) const;
};


class Coordinates
{
friend class CoordinatesSystem;
friend class DistanceVector;

private:
    const CoordinatesSystem* const system;
    const float x;
    const float y;

    Coordinates(float, float, const CoordinatesSystem* const);

public:
    const Coordinates transform_to(const CoordinatesSystem&) const;
    const Vector operator*(const UnitVector&) const;
    const DistanceVector operator-(const Coordinates&) const;
    const Coordinates operator+(const DistanceVector&) const;
    const Coordinates operator-(const DistanceVector&) const;
};


class Vector
{
    friend class UnitVector;
    friend class Coordinates;
protected:
    const float x;
    const float y;

public:
    Vector(float, float);
};


class DistanceVector : protected Vector
{    
    friend class Coordinates;
public:
    DistanceVector(float, float);
    const Coordinates operator+(const Coordinates&) const;
    const DistanceVector operator+(const DistanceVector&) const;
    const DistanceVector operator-(const DistanceVector&) const;
};


class UnitVector : public Vector
{    
public:
    UnitVector(float, float);
    explicit UnitVector(const Vector&);
    const DistanceVector operator*(float) const;
};
#endif
