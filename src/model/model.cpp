#include "model/model.h"
#include "common.h"

Model::Model()
{

}

void Model::create_new_game(const RealTime &time)
{
  world_ = std::unique_ptr<World>(new World(this));
  clock_ = std::unique_ptr<SimulationClock>(
    new SimulationClock(AbsoluteTime(0)));
  clock_->start(time);
}

void Model::update(const RealTime &realtime)
{
  auto simulation_time = clock_->to_simulation_time(realtime);
  world_->update(simulation_time);
  LOG(realtime);
}

const RealTime Model::get_next_event_time() const
{
  auto earliest_event_time = world_->get_next_event_time();
  return clock_->to_realtime(earliest_event_time);
}

const ViewModel Model::get_viewmodel() const
{
  return ViewModel(world_->get_objects());
}
