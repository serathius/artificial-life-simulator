#include "model/model.h"
#include "common.h"

Model::Model()
{

}

void Model::create_new_game(const RealTime& time)
{
    world_ = std::unique_ptr<World>(new World(this));
    clock_ = std::unique_ptr<SimulationClock>(
      new SimulationClock(AbsoluteTime(0)));
    clock_->start(time);
}

void Model::update(const RealTime& realtime)
{
    auto simulation_time = clock_->to_simulation_time(realtime);
    LOG(realtime);
    for (auto event_object: event_objects_)
    {
        event_object->update(simulation_time);
    }
}

const RealTime Model::get_next_event_time() const
{
    AbsoluteTime earliest_event_time =
        (*event_objects_.begin())->get_next_event_time();
    for (auto event_object: event_objects_)
    {
        auto event_time = event_object->get_next_event_time();
        if (earliest_event_time > event_time)
            earliest_event_time = event_time;
    }
    LOG(earliest_event_time);
    return clock_->to_realtime(earliest_event_time);
}

const ViewModel Model::get_viewmodel() const
{
    return ViewModel(world_->get_objects());
}

void Model::register_event_object(EventObject *event_object)
{
    event_objects_.add(event_object);
}
