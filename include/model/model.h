#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <set>

class EventObject;
class EventObjectCollection;
class Model;
class ModelObject;
class World;


#include "simulation_clock.h"


class EventObjectCollection
{
private:
    std::set<EventObject*> event_objects_;

public:
    typedef std::set<EventObject*>::iterator Iterator;
    Iterator begin() const;
    Iterator end() const;
    void add(EventObject*);
    void remove(EventObject*);
};


class Model
{
private:
    std::unique_ptr<World> world_;
    std::unique_ptr<SimulationClock> clock_;
    EventObjectCollection event_objects_;

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
    virtual void update(const AbsoluteTime&) = 0;
};

#include "world.h"

#endif
