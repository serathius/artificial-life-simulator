#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <set>
#include <map>
#include <memory>

class WorldObjectsCollection;
class Model;

#include "objects.h"
#include "primitives.h"

class EventObjectCollection
{
public:
  typedef std::set<std::shared_ptr<EventObject>>::iterator Iterator;

  Iterator begin() const;
  Iterator end() const;
  void add(std::shared_ptr<EventObject>);
  void remove(std::shared_ptr<EventObject>);

private:
  std::set<std::shared_ptr<EventObject>> event_objects_;
};


struct Position
{
  Coordinates coordinates;
  UnitVector direction;
};


class WorldObjectsCollectionIterator
{
private:
  std::map<std::shared_ptr<WorldObject>, Position>::const_iterator iterator_;

public:
  WorldObjectsCollectionIterator(const std::map<std::shared_ptr<WorldObject>, Position>::const_iterator &iterator) {iterator_ = iterator;}
  WorldObjectsCollectionIterator& operator++();
  bool operator==(const WorldObjectsCollectionIterator&);
  bool operator!=(const WorldObjectsCollectionIterator&);
  std::shared_ptr<WorldObject> operator*();
};


class WorldObjectsCollection
{
public:
  WorldObjectsCollection(Model* const model);
  typedef WorldObjectsCollectionIterator iterator;
  iterator begin() const;
  iterator end() const;
  void add(std::shared_ptr<WorldObject>, const Coordinates&, const UnitVector&);
  void remove(WorldObject*);
  const WorldObjectViewCollection get_view() const;

private:
  typedef std::pair<std::shared_ptr<WorldObject>, Position> element;
  Model* const model_;
  std::map<std::shared_ptr<WorldObject>, Position> objects_;

};

#endif /* COLLECTIONS_H_ */
