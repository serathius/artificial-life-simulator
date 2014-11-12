#include <cmath>

#include <GL/glu.h>

#include "view/camera.h"

void Camera::look()
{
    Coordinates up_vector;
    float x = position.x - target.x;
    float y = position.y - target.y;
    float z = position.z - target.z;
    up_vector.x = ( -x / std::sqrt( x*x + y*y ) ) * z;
    up_vector.y = ( -y / std::sqrt( x*x + y*y ) ) * z;
    up_vector.z = std::sqrt( x*x + y*y );
    gluLookAt(position.x, position.y, position.z, target.x, target.y, target.z,
              up_vector.x, up_vector.y, up_vector.z);
}


void Camera::move(float axis_x, float axis_y, float axis_z)
{
    position.x += axis_x;
    position.y += axis_y;
    position.z += axis_z;
    look();
}


void Camera::set_position(float axis_x, float axis_y, float axis_z)
{
    position.x = axis_x;
    position.y = axis_y;
    position.z = axis_z;
    look();
}


void Camera::set_target(float axis_x, float axis_y, float axis_z)
{
    target.x = axis_x;
    target.y = axis_y;
    target.z = axis_z;
    look();
}
/*
 * camera.cpp
 *
 *  Created on: 12 lis 2014
 *      Author: matfil
 */




