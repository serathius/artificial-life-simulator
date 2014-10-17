#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>

#include "world.h"
#include "simulation_clock.h"


class Model
{
private:
    std::unique_ptr<World> world;
    std::unique_ptr<SimulationClock> clock;
    EventObjectCollection event_objects;

public:
    void update(const RealTime&);
    const RealTime get_next_event_time() const;
};


class EventObjectCollection
{
private:
    std::vector<EventObject*> events;

public:
    EventObjectCollection();
    void add(EventObject*);
    void remove(EventObject*);
};


class EventObject
{
public:
    EventObject();
    virtual AbsoluteTime& get_next_event_time() = 0;
};

#endif
