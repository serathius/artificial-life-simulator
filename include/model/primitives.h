#ifndef COORDINATES_SYSTEM_H
#define COORDINATES_SYSTEM_H

class DistanceVector;
class UnitVector;
class Vector;


class Coordinates
{
friend class Vector;

private:
    const float x_;
    const float y_;

public:
    Coordinates(float, float);
    const Vector operator*(const UnitVector&) const;
    const DistanceVector operator-(const Coordinates&) const;
    const Coordinates operator+(const DistanceVector&) const;
    const Coordinates operator-(const DistanceVector&) const;
    bool operator==(const Coordinates&) const;
};


class Dimension
{
private:
    const float x_;
    const float y_;

public:
    Dimension(float x, float y);
    bool operator==(const Dimension &other) const;
    bool operator!=(const Dimension &other) const;
    const Coordinates operator+(const Coordinates &point) const;
    const Vector to_vector() const;
};

class Vector
{
    friend class Coordinates;

private:
    const float x_;
    const float y_;

public:
    Vector(float, float);
    const Coordinates operator+(const Coordinates&) const;
    const Vector operator+(const Vector&) const;
    const Vector operator-(const Vector&) const;
    bool operator==(const Vector&) const;
};


class UnitVector : public Vector
{
private:
    const float x_;
    const float y_;

public:
    UnitVector(float, float);
    explicit UnitVector(const Vector&);
    bool operator==(const UnitVector&) const;
};
#endif
