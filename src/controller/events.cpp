#include <string>

#include "controller/events.h"


StringEvent::StringEvent(string message)
{
    this->message = message;
}

string StringEvent::getMessage()
{
    return message;
}

Event::~Event()
{

}

StringEvent::~StringEvent()
{

}
