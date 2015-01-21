#include <assert.h>
#include "model/world.h"

#include "model/organism.h"


World::World(Model* const model) : objects_(WorldObjectsCollection(model))
{
  assert(objects_.add(
    new WorldPlane(this, Distance(1)), Coordinates(0, 0), UnitVector(0)));
  assert(objects_.add(
    new Organism(this, AbsoluteTime(0)), Coordinates(0, 0), UnitVector(0)));
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
    delete object_ptr.first;
  }
}

bool WorldObjectsCollection::add(WorldObject* object,
  const Coordinates& coordinates, const UnitVector& direction)
{
  Shape* first_shape = object->get_shape(coordinates, direction);
  for (auto pair: objects_)
  {
    Shape* second_shape = pair.first->get_shape(pair.second.coordinates,
      pair.second.direction);
    if (are_intersecting(*first_shape, *second_shape))
    {
      delete first_shape;
      delete second_shape;
      return false;
    }
      delete second_shape;
  }
  delete first_shape;
  objects_.insert(element(object, {coordinates, direction}));
  EventObject* event_object = dynamic_cast<EventObject*>(object);
  if (event_object != nullptr)
  {
    model_->register_event_object(event_object);
  }
  return true;
}

const WorldObjectViewCollection WorldObjectsCollection::get_view() const
{
  WorldObjectViewCollection result;
  for (auto pair: objects_)
  {
    WorldObjectView* view_object = pair.first->get_view(
      pair.second.coordinates, pair.second.direction);
    result.push_back(std::shared_ptr<WorldObjectView>(view_object));
  }
  return result;
}

const WorldObjectViewCollection World::get_objects() const
{
  return objects_.get_view();
}

WorldObjectsCollection::iterator WorldObjectsCollection::begin() const
{
  return iterator(objects_.begin());
}

WorldObjectsCollection::iterator WorldObjectsCollection::end() const
{
  return iterator(objects_.end());
}


WorldPlane::WorldPlane(World *const world, Distance const & distance)
  : WorldObject(world), distance_(distance)
{

}

WorldObjectView* WorldPlane::get_view(Coordinates const &coordinates,
  UnitVector const &direction)
{
  return new CircleWorldObjectView(coordinates, distance_);
}

Shape* WorldPlane::get_shape(const Coordinates& coordinates, const UnitVector&)
{
  return new ReverseCircle(coordinates, distance_);
}
