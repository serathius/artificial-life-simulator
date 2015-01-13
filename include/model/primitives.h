#ifndef COORDINATES_SYSTEM_H
#define COORDINATES_SYSTEM_H

class DistanceVector;
class UnitVector;
class Vector;


class Coordinates
{
friend class DistanceVector;

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
    friend class UnitVector;
    friend class Coordinates;
protected:
    const float x_;
    const float y_;

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
    bool operator==(const DistanceVector&) const;
};


class UnitVector : public Vector
{    
public:
    UnitVector(float, float);
    explicit UnitVector(const Vector&);
    const DistanceVector operator*(float) const;
    bool operator==(const UnitVector&) const;
};
#endif
