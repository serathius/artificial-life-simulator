#ifndef COORDINATES_SYSTEM_H
#define COORDINATES_SYSTEM_H

class CoordinatesSystem
{
private:
    #macierz transformacji

public:
    CoordinatesSystem();
    const Coordinates& get_coordinates(float x, float y) const;
};

class Coordinates
{
friend CoordinatesSystem;
private:
    CoordinatesSystem* const system;
    const float x;
    const float y;

    Coordinates(float, float, CoordinatesSystem*);

public:
    const Vector& operator-(const Coordinates&) const;
    const Coordinates& transform_to(const CoordinatesSystem&) const;

};

class Vector
{
private:
    const float x;
    const float y;

public:
    Vector(float, float);
    const Vector& operator+(const Vector&) const;
    const Vector& operator-(const Vector&) const;
};

class DistanceVector : public Vector
{
public:
    DistanceVector(float, float);
    const Coordinates& operator+(const Coordinates&) const;
};

class UnitVector: public Vector
{
public:
    UnitVector(float, float);
    UnitVector(const Vector&);
};
#endif
