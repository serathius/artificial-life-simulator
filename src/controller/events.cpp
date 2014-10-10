#include "controller/events.h"
#include <string>

using namespace std;

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
