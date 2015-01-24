#include <assert.h>

#include "model/collections.h"
#include "model/model.h"

void EventObjectCollection::add(std::shared_ptr<EventObject> event_object)
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

void WorldObjectsCollection::add(std::shared_ptr<WorldObject> object,
  const Coordinates &coordinates, const UnitVector &direction)
{
  std::shared_ptr<Shape> first_shape = object->get_shape(coordinates, direction);
  std::shared_ptr<Shape> second_shape;
  for (auto pair: objects_)
  {
    second_shape = pair.first->get_shape(pair.second.coordinates,
                                         pair.second.direction);
    assert(!are_intersecting(*first_shape, *second_shape));
  }
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

WorldObjectsCollectionIterator WorldObjectsCollection::begin() const
{
  return WorldObjectsCollectionIterator(objects_.begin());
}

WorldObjectsCollectionIterator WorldObjectsCollection::end() const
{
  return WorldObjectsCollectionIterator(objects_.end());
}

WorldObjectsCollectionIterator& WorldObjectsCollectionIterator::operator++()
{
  ++iterator_;
  return *this;
}

bool WorldObjectsCollectionIterator::operator==(const WorldObjectsCollectionIterator& it)
{
  return iterator_== it.iterator_;
}

bool WorldObjectsCollectionIterator::operator!=(const WorldObjectsCollectionIterator& it)
{
  return iterator_!= it.iterator_;
}

std::shared_ptr<WorldObject> WorldObjectsCollectionIterator::operator*()
{
  return iterator_->first;
}
