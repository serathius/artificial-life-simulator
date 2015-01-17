#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <set>

class EventObject;
class EventObjectCollection;
class Model;
class ModelObject;
class World;
class ViewModel;

#include "simulation_clock.h"
#include "view/viewmodel.h"

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
    Model();
    void create_new_game();
    void update(const RealTime&);
    const RealTime get_next_event_time() const;
    void register_event_object(EventObject* event_object);
    const ViewModel get_viewmodel() const;
};


class EventObject
{
public:
    virtual const AbsoluteTime get_next_event_time() = 0;
    virtual void update(const AbsoluteTime&) = 0;
};

#include "world.h"

#endif
