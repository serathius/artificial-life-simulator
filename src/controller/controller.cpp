#include "controller/controller.h"
#include <typeindex>
#include "controller/blocking_queue.h"
#include <iostream>
#include "controller/events.h"
#include <utility>


Controller::Controller(EventQueue* const event_queue)
{
    this->event_queue = event_queue;
    this->strategyMap.insert(std::make_pair<std::type_index, StringStrategy*>
            (std::type_index(typeid(StringEvent)), new StringStrategy()));
}

void Controller::handle_events()
{
    while(true)
    {
        Event* event;
        event = event_queue->pop();
        ControllerStrategy* strategy =
            strategyMap[(std::type_index(typeid(*event)))];
        strategy->react(event);

    }
}

void Controller::StringStrategy::react(Event* event)
{
    StringEvent* stringEven =
        dynamic_cast<StringEvent*>(event);
}

Controller::ControllerStrategy::ControllerStrategy()
{

}

void Controller::ControllerStrategy::react(Event* event)
{

}