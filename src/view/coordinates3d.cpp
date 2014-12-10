#include <cmath>

#include "view/coordinates3d.h"

view::Coordinates::Coordinates(float var_x = 0,
                               float var_y = 0,
                               float var_z = 0)
{
    x = var_x;
    y = var_y;
    z = var_z;
}


view::Coordinates::Coordinates(): x(0), y(0), z(0)
{
}


view::Vector view::Coordinates::operator-(const view::Coordinates& other) const
{
    return view::Vector(
                        this -> x - other.x,
                        this -> y - other.y,
                        this -> z - other.z);
}


bool view::Coordinates::operator ==(const view::Coordinates& right) const
{
    return this->x == right.x
       and this->y == right.y
       and this->z == right.z;
}


view::Vector get_orthogonal(const view::Vector& vector)
{
    view::Vector up_vector;
    up_vector.x = ( -vector.x / std::sqrt( vector.x*vector.x + vector.y*vector.y ) ) * vector.z;
    up_vector.y = ( -vector.y / std::sqrt( vector.x*vector.x + vector.y*vector.y ) ) * vector.z;
    up_vector.z = std::sqrt( vector.x*vector.x + vector.y*vector.y );
    return up_vector;
}


view::Vector::Vector() :x(0), y(0), z(0)
{
}


view::Vector::Vector(float axis_x, float axis_y, float axis_z)
{
    x = axis_x;
    y = axis_y;
    z = axis_z;
}

view::Coordinates view::Coordinates::operator+(const view::Vector& vector) const
{
    view::Coordinates temp(this->x + vector.x,
                           this->y + vector.y,
                           this->z + vector.z);
    return temp;


}

const float view::Vector::length()
{

    return std::sqrt(x*x + y*y + z*z);

}

void view::Vector::normalize()
{
    float l = this->length();
    x = x/l;
    y = y/l;
    z = z/l;
}

const view::Vector view::Vector::operator * (const float value)
{
    view::Vector temp(this->x * value,
                      this->y * value,
                      this->z * value);
    return temp;
}
