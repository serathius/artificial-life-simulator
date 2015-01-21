#ifndef MODEL_H
#define MODEL_H

#include <memory>

class Model;

#include "simulation_clock.h"
#include "view/viewmodel.h"

#include "world.h"

class Model
{
public:
  Model();
  void create_new_game(const RealTime&);
  void update(const RealTime&);
  const RealTime get_next_event_time() const;
  const ViewModel get_viewmodel() const;

private:
  std::unique_ptr<World> world_;
  std::unique_ptr<SimulationClock> clock_;
};

#endif /* MODEL_H */
