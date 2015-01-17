#include "model/organism.h"

#include <GLFW/glfw3.h>
#include <cmath>

Organism::Organism(World * const world, const Coordinates &coordinates, const UnitVector &direction)
  : WorldObject(world), coordinates_(coordinates),
    direction_(direction), genotype_(Genotype()), logic_(OrganismLogic())
{

}

void Organism::draw()
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

void Organism::update(AbsoluteTime const &time)
{

}

const AbsoluteTime Organism::get_next_event_time()
{
  return AbsoluteTime(0);
}
