#include <typeindex>
#include <iostream>
#include <utility>

#include "controller/controller.h"


Controller::Controller() : view_(&event_queue_)
{

}

void Controller::start()
{
    view_.start();
    model_.create_new_game();
    handle_events();
    view_.finish();
}

void Controller::handle_events()
{
    while(true)
    {
        view_.update(model_.get_viewmodel());
        Event* event = event_queue_.pop();
        ControllerStrategy* strategy =
            strategyMap[std::type_index(typeid(*event))];
        strategy->react(event);
    }
}

void StringStrategy::react(Event* event)
{

}

ControllerStrategy::ControllerStrategy()
{

}

void ControllerStrategy::react(Event* event)
{

}
