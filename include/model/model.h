#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <set>

class EventObject;
class EventObjectCollection;
class Model;
class ModelObject;
class World;
class ViewModel;

#include "simulation_clock.h"
#include "view/viewmodel.h"
#include "model/objects.h"

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


class Model
{
public:
  Model();
  void create_new_game(const RealTime& time);
  void update(const RealTime&);
  const RealTime get_next_event_time() const;
  void register_event_object(EventObject* event_object);
  const ViewModel get_viewmodel() const;

private:
  std::unique_ptr<World> world_;
  std::unique_ptr<SimulationClock> clock_;
  EventObjectCollection event_objects_;
};

#endif /* MODEL_H */
