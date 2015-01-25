#include "controller/controller.h"
#include "controller/events.h"

Event::~Event()
{

}

void UpdateModelEvent::accept(Controller *controller)
{
  controller->visit(this);
}

void ExitEvent::accept(Controller *controller)
{
    controller->visit(this);
}
