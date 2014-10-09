#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include "blocking_queue.h"
#include "events.h"

class Controller
{

public:
    typedef BlockingQueue<Event*> EventQueue;
    EventQueue* const event_queue;
public:
    Controller(Model* const, View* const, EventQueue* const);
    void handle_events();

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
private:
    std::unordered_map<std::type_index, ControllerStrategy*> strategyMap;
    EventQueue* event_queue;

};

#endif