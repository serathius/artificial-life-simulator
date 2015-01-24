#include "view/viewmodel.h"

#include <GLFW/glfw3.h>
#include <cmath>

void ViewModel::draw()
{
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
  const UnitVector &direction) : coordinates_(coordinates), direction_(direction)
{

}

void TriangleWorldObjectView::draw()
{
  float x = coordinates_.get_x();
  float y = coordinates_.get_y();
  float r = 0.2f;
  glColor3f(1.0f, 0.f, 0.f);
  glTranslatef(x, y, 0.f);
  glRotatef(direction_.get_angle() - 30, 0, 0, -1);
  glBegin(GL_TRIANGLES);
  glVertex2f(- r / 2, - r * (float) sqrt(3) / 6);
  glVertex2f(0.f, r * (float) sqrt(3) / 3);
  glVertex2f(r / 2, - r * (float) sqrt(3) / 6);
  glEnd();
  glRotatef(-(direction_.get_angle() - 30), 0, 0, -1);
  glTranslatef(-x, -y, 0.f);
}

SquareWorldObjectView::SquareWorldObjectView(const Coordinates &coordinates,
  const UnitVector &direction, const Dimension &dimension) : coordinates_(coordinates),
                                 direction_(direction), dimension_(dimension)
{

}

void SquareWorldObjectView::draw()
{
  glColor3f(0.f, 0.5f, 0.f);
  glBegin(GL_QUADS);
  glVertex2f(0, 0);
  glVertex2f(dimension_.get_x(), 0);
  glVertex2f(dimension_.get_x(), dimension_.get_y());
  glVertex2f(0, dimension_.get_y());
  glEnd();
}

CircleWorldObjectView::CircleWorldObjectView(const Coordinates &coordinates,
  const Distance &distance) : coordinates_(coordinates), distance_(distance)
{

}

void CircleWorldObjectView::draw()
{
  glColor3f(0.f, 0.5f, 0.f);
  float theta = static_cast<float>(2 * M_PI / SEGMENTS_COUNT);
  float tangetial_factor = tanf(theta);
  float radial_factor = cosf(theta);
  float dx = distance_.get_distance();
  float dy = 0.f;
  glBegin(GL_POLYGON);
  for (int i=0; i<SEGMENTS_COUNT; ++i)
  {
    glVertex2f(coordinates_.get_x() + dx, coordinates_.get_y() + dy);
    float tmp_x = (dx - dy * tangetial_factor) * radial_factor;
    dy = (dy + dx * tangetial_factor) * radial_factor;
    dx = tmp_x;
  }
  glEnd();
}
