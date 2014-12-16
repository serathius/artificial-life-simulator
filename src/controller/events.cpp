#include <string>

#include "controller/events.h"


StringEvent::StringEvent(std::string message_text)
{
	message = message_text;
}

std::string StringEvent::getMessage()
{
    return message;
}

Event::~Event()
{

}

StringEvent::~StringEvent()
{

}
