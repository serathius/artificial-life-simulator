#include "model/world.h"

#include <GLFW/glfw3.h>

#include "model/organism.h"


World::World(Model* const model) : objects_(WorldObjectsCollection(model))
{
  objects_.add(
    new WorldPlane(this, Dimension(1, 1)));
  objects_.add(
    new Organism(this, Coordinates(0.5, 0.5), UnitVector(90), AbsoluteTime(0)));
}

WorldObject::WorldObject(World *const world)
 : world_(world)
{

}

WorldObject::~WorldObject()
{

}

WorldObjectsCollection::WorldObjectsCollection(Model* const model)
  : model_(model)
{

}

WorldObjectsCollection::~WorldObjectsCollection()
{
  for(auto object_ptr: objects_)
  {
    delete object_ptr;
  }
}

void WorldObjectsCollection::add(WorldObject* object)
{
  objects_.insert(object);
  EventObject* event_object = dynamic_cast<EventObject*>(object);
  if (event_object != nullptr)
  {
    model_->register_event_object(event_object);
  }
}

const std::vector<WorldObject*> World::get_objects() const
{
  std::vector<WorldObject*> result;
  for (auto object_unique_ptr: objects_)
  {
    result.push_back(object_unique_ptr);
  }
  return result;
}

WorldObjectsCollection::iterator WorldObjectsCollection::begin() const
{
  return objects_.begin();
}

WorldObjectsCollection::iterator WorldObjectsCollection::end() const
{
  return objects_.end();
}


WorldPlane::WorldPlane(World *const world, Dimension const & dimension)
  : WorldObject(world), dimension_(dimension)
{

}

void WorldPlane::draw()
{
  glColor3f(0.f, 0.5f, 0.f);
  glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(dimension_.get_x(), 0);
    glVertex2f(dimension_.get_x(), dimension_.get_y());
    glVertex2f(0, dimension_.get_y());
  glEnd();
}
