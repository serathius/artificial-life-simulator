#ifndef MODEL_H
#define MODEL_H

#include <memory>

class Model;

#include "simulation_clock.h"
#include "view/viewmodel.h"
#include "collections.h"
#include "world.h"

class Model
{
public:
  Model();
  void create_new_game(const RealTime&);
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
