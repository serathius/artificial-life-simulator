#ifndef COORDINATES_SYSTEM_H
#define COORDINATES_SYSTEM_H


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
    const Vector operator-(const Coordinates&) const;
    const Coordinates operator+(const Vector&) const;
    const Coordinates operator-(const Vector&) const;
    bool operator==(const Coordinates&) const;
    float get_x();
    float get_y();
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
    float get_x();
    float get_y();
};

class Vector
{
    friend class Coordinates;
    friend class UnitVector;
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


class UnitVector
{
    friend class Coordinates;

private:
    float angle_;

public:
    UnitVector(float);
    explicit UnitVector(const Vector&);
    UnitVector& operator=(const UnitVector&);
    const UnitVector operator+(const UnitVector&) const;
    bool operator==(const UnitVector&) const;
    float get_angle();
};
#endif
