#ifndef MODEL_H
#define MODEL_H

class EventObject;
class EventObjectCollection;
class Model;
class ModelObject;
class World;

#include <memory>
#include <set>

#include "simulation_clock.h"

typedef std::set<EventObject*>::iterator EventObjectIterator;

class EventObjectCollection
{
private:
    std::set<EventObject*> event_objects;

public:
    EventObjectIterator begin();
    EventObjectIterator end();
    void add(EventObject*);
    void remove(EventObject*);
};


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


class ModelObject
{


};


class EventObject : public ModelObject
{
public:
    EventObject();
    virtual AbsoluteTime& get_next_event_time() = 0;
};

#include "world.h"

#endif
