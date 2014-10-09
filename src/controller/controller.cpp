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
    while(1)
    {
        Event* event;
        event = event_queue->pop();
        ControllerStrategy* strategy =
        strategyMap[(std::type_index(typeid(*event)))];
        std::cout<<"reacting"<<endl;
        strategy->react(event);

    }
}

void Controller::StringStrategy::react(Event* event)
{
    StringEvent* stringEvent
            = dynamic_cast<StringEvent*>(event);
    std::cout<<stringEvent->getMessage();
}

Controller::ControllerStrategy::ControllerStrategy()
{

}

void Controller::ControllerStrategy::react(Event* event)
{

}