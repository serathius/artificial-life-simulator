#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <set>
#include <map>

class WorldObjectsCollection;
class Model;

#include "objects.h"
#include "primitives.h"

class EventObjectCollection
{
public:
  typedef std::set<EventObject*>::iterator Iterator;

  Iterator begin() const;
  Iterator end() const;
  void add(EventObject*);
  void remove(EventObject*);

private:
  std::set<EventObject*> event_objects_;
};


struct Position
{
  Coordinates coordinates;
  UnitVector direction;
};


class WorldObjectsCollection
{
private:
  typedef std::pair<WorldObject*, Position> element;
  Model* const model_;
  std::map<WorldObject*, Position> objects_;

public:
  WorldObjectsCollection(Model* const model);
  ~WorldObjectsCollection();
  class iterator
  {
  private:
    std::map<WorldObject*, Position>::const_iterator iterator_;
  public:
    iterator(const std::map<WorldObject*, Position>::const_iterator& iterator)
    {
      iterator_ = iterator;
    }
    iterator& operator++() {++iterator_;return *this;}
    iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
    bool operator==(const iterator& rhs) {return iterator_==rhs.iterator_;}
    bool operator!=(const iterator& rhs) {return iterator_!=rhs.iterator_;}
    WorldObject* operator*() {return iterator_->first;}
  };
  iterator begin() const;
  iterator end() const;
  bool add(WorldObject*, const Coordinates&, const UnitVector&);
  void remove(WorldObject*);
  const WorldObjectViewCollection get_view() const;
};

#endif /* COLLECTIONS_H_ */
