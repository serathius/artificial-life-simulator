#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

class ControllerStrategy;

#include "controller/event_queue.hpp"
#include "model/model.h"
#include "view/view.h"


class Controller
{
private:
    Model model_;
    View view_;
    EventQueue event_queue_;

    std::unordered_map<std::type_index, ControllerStrategy*> strategyMap;
    void handle_events();

public:
    Controller();
    void start();
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
