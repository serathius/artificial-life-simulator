#include "model/world.h"

#include "model/organism.h"


World::World(Model* const model) : objects_(WorldObjectsCollection(model))
{
  objects_.add(
    new WorldPlane(this, Dimension(1, 1)), Coordinates(0, 0), UnitVector(0));
  objects_.add(
    new Organism(this, AbsoluteTime(0)), Coordinates(0.5, 0.5), UnitVector(90));
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

void WorldObjectsCollection::add(WorldObject* object,
  const Coordinates& coordinates, const UnitVector& direction)
{
  objects_.insert(element(object, {coordinates, direction}));
  EventObject* event_object = dynamic_cast<EventObject*>(object);
  if (event_object != nullptr)
  {
    model_->register_event_object(event_object);
  }
}

const std::vector<std::shared_ptr<WorldObjectView>> WorldObjectsCollection::get_view() const
{
  std::vector<std::shared_ptr<WorldObjectView>> result;
  for (auto pair: objects_)
  {
    WorldObjectView* view_object = pair.first->get_view(
      pair.second.coordinates, pair.second.direction);
    result.push_back(std::shared_ptr<WorldObjectView>(view_object));
  }
  return result;
}

const std::vector<std::shared_ptr<WorldObjectView>> World::get_objects() const
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


WorldPlane::WorldPlane(World *const world, Dimension const & dimension)
  : WorldObject(world), dimension_(dimension)
{

}

WorldObjectView* WorldPlane::get_view(Coordinates const &coordinates,
  UnitVector const &direction)
{
  return new SquareWorldObjectView(coordinates, direction, dimension_);
}