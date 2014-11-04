#include "model/model.h"

void Model::update(const RealTime& realtime)
{
    auto simulation_time = this->clock->to_simulation_time(realtime);
    for (auto event_object: this->event_objects)
    {
        event_object->update(simulation_time);
    }
}

const RealTime Model::get_next_event_time() const
{
    AbsoluteTime earliest_event_time =
        (*this->event_objects.begin())->get_next_event_time();
    for (auto event_object: this->event_objects)
    {
        auto event_time = event_object->get_next_event_time();
        if (earliest_event_time > event_time)
            earliest_event_time = event_time;
    }
    return this->clock->to_realtime(earliest_event_time);
}

EventObjectCollection::Iterator EventObjectCollection::begin() const
{
    return this->event_objects.begin();
}

EventObjectCollection::Iterator EventObjectCollection::end() const
{
    return this->event_objects.end();
}
