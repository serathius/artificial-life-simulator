#include "model/model.h"

void Model::update(const RealTime& realtime)
{
    auto simulation_time = clock_->to_simulation_time(realtime);
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
    return clock_->to_realtime(earliest_event_time);
}

EventObjectCollection::Iterator EventObjectCollection::begin() const
{
    return event_objects_.begin();
}

EventObjectCollection::Iterator EventObjectCollection::end() const
{
    return event_objects_.end();
}
