#include <algorithm>
#include <cmath>

#include <GLFW/glfw3.h>

#include "view/viewmodel.h"

bool cmp_obj_z(std::shared_ptr<WorldObjectView> first,
        std::shared_ptr<WorldObjectView> second)
{
    return first->get_z() < second->get_z();
}

void ViewModel::draw()
{
  sort(objects_.begin(), objects_.end(), cmp_obj_z);
  for (auto object: objects_)
  {
    object->draw();
  }
}

ViewModel::ViewModel(const WorldObjectViewCollection &objects)
{
  objects_ = objects;
}

TriangleWorldObjectView::TriangleWorldObjectView(const Coordinates &coordinates,
  const UnitVector &direction, float z, const Color &color)
  : coordinates_(coordinates), direction_(direction), z_(z), color_(color)
{

}

void TriangleWorldObjectView::draw()
{
  float x = coordinates_.get_x();
  float y = coordinates_.get_y();
  float r = 0.2f;
  glTranslatef(x, y, z_);
  glRotatef(direction_.get_angle() - 90, 0, 0, 1);
  glColor3f(color_.R, color_.G, color_.B);
  glBegin(GL_TRIANGLES);
    glVertex2f(- r / 2, - r * (float) sqrt(3) / 6);
    glVertex2f(0.f, r * (float) sqrt(3) / 3);
    glVertex2f(r / 2, - r * (float) sqrt(3) / 6);
  glEnd();
  glRotatef(direction_.get_angle() - 90, 0, 0, -1);
  glTranslatef(-x, -y, -z_);
}

SquareWorldObjectView::SquareWorldObjectView(const Coordinates &coordinates,
  const UnitVector &direction, const Dimension &dimension, float z,
  const Color &color)
  : coordinates_(coordinates), direction_(direction), dimension_(dimension),
    z_(z), color_(color)
{

}

void SquareWorldObjectView::draw()
{
  glColor3f(color_.R, color_.G, color_.B);
  glBegin(GL_QUADS);
  glVertex3f(0, 0, z_);
  glVertex3f(dimension_.get_x(), 0, z_);
  glVertex3f(dimension_.get_x(), dimension_.get_y(), z_);
  glVertex3f(0, dimension_.get_y(), z_);
  glEnd();
}

CircleWorldObjectView::CircleWorldObjectView(const Coordinates &coordinates,
  const Distance &distance, float z, const Color &color)
  : coordinates_(coordinates), distance_(distance), z_(z), color_(color)
{

}

void CircleWorldObjectView::draw()
{
  glColor3f(color_.R, color_.G, color_.B);
  float theta = static_cast<float>(2 * M_PI / SEGMENTS_COUNT);
  float tangetial_factor = tanf(theta);
  float radial_factor = cosf(theta);
  float dx = distance_.get_distance();
  float dy = 0.f;
  glBegin(GL_POLYGON);
  for (int i=0; i<SEGMENTS_COUNT; ++i)
  {
    glVertex3f(coordinates_.get_x() + dx, coordinates_.get_y() + dy, z_);
    float tmp_x = (dx - dy * tangetial_factor) * radial_factor;
    dy = (dy + dx * tangetial_factor) * radial_factor;
    dx = tmp_x;
  }
  glEnd();
}
