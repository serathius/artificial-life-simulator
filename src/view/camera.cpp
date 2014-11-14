#include <cmath>

#include <GL/glu.h>

#include "view/camera.h"
#include "view/coordinates3d.h"

Camera::Camera() : near(1), far(3), width(1), height(9/16)
{
    view::Coordinates first_target(1, 1, 1);
    target = first_target;
    look();
}

void Camera::look()
{

    view::Vector up_vector = get_orthogonal(target - position);

    gluLookAt(position.x, position.y, position.z, target.x, target.y, target.z,
              up_vector.x, up_vector.y, up_vector.z);
}


void Camera::move(view::Vector& vector)
{
    position = position + vector;
    look();
}

void Camera::set_depth(float depth)
{
    far = near + depth;
    glFrustum(height,height,width,width,near,far);
}

void Camera::set_position(view::Coordinates point)
{
    position = point;
    look();
}

void Camera::set_perspective(float view_width, float view_height,
                             float view_depth)
{
    width = view_width;
    height = view_height;
    far = near + view_depth;
    glFrustum(height,height,width,width,near,far);

}

void Camera::set_target(view::Coordinates point)
{
    target = point;
    look();
}

void Camera::move_to(view::Coordinates coordinates)
{
    view::Vector vector;
    vector = coordinates - position;
    this->move(vector);


}

void Camera::set_zoom(float n)
{
    near = n;
    glFrustum(height,height,width,width,near,far);
}

