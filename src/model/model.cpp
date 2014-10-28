#include "model/model.h"

void Model::update(const RealTime& realtime)
{
    auto simulation_time = this->clock->to_simulation_time(realtime);
    for (auto event_object: this->event_objects)
    {
        event_object->update(simulation_time);
    }
}

EventObjectCollection::Iterator EventObjectCollection::begin() const
{
    return this->event_objects.begin();
}

EventObjectCollection::Iterator EventObjectCollection::end() const
{
    return this->event_objects.end();
}
