#include "controller/events.h"
#include "controller/controller.h"

Event::~Event()
{

}

void UpdateModelEvent::accept(Controller* controller)
{
  controller->visit(this);
}
