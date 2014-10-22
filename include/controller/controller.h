#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

class ControllerStrategy;

#include "controller/event_queue.hpp"


class Controller
{
private:
    EventQueue* const event_queue;
    std::unordered_map<std::type_index, ControllerStrategy*> strategyMap;

public:
    Controller(EventQueue* const);
    void handle_events();
};


class ControllerStrategy
{
public:
    virtual void react(Event* event);
    ControllerStrategy();
};


class StringStrategy: public ControllerStrategy
{
public:
    virtual void react(Event* event);
};
#endif
