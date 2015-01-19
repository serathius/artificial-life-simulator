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

ViewModel::ViewModel(const std::vector<std::shared_ptr<WorldObjectView>> &objects)
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
  glRotatef(direction_.get_angle(), 0, 0, -1);
  glBegin(GL_TRIANGLES);
  glVertex2f(- r / 2, - r * (float) sqrt(3) / 6);
  glVertex2f(0.f, r * (float) sqrt(3) / 3);
  glVertex2f(r / 2, - r * (float) sqrt(3) / 6);
  glEnd();
  glRotatef(-direction_.get_angle(), 0, 0, -1);
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