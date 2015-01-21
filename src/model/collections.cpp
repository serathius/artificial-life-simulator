#include <assert.h>

#include "model/collections.h"
#include "model/model.h"

void EventObjectCollection::add(EventObject *event_object)
{
  event_objects_.insert(event_object);
}

EventObjectCollection::Iterator EventObjectCollection::begin() const
{
  return event_objects_.begin();
}

EventObjectCollection::Iterator EventObjectCollection::end() const
{
  return event_objects_.end();
}

WorldObjectsCollection::WorldObjectsCollection(Model* const model)
: model_(model)
{

}

void WorldObjectsCollection::add(WorldObject* object,
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
      assert(false);
    }
    delete second_shape;
  }
  delete first_shape;
  objects_.insert(element(object, {coordinates, direction}));
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

WorldObjectsCollection::iterator WorldObjectsCollection::begin() const
{
  return iterator(objects_.begin());
}

WorldObjectsCollection::iterator WorldObjectsCollection::end() const
{
  return iterator(objects_.end());
}
