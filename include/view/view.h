#ifndef VIEW_H
#define VIEW_H

#include "controller/event_queue.hpp"

class View
{
private:
    EventQueue* const event_queue;

public:
    View(EventQueue * const);
};

#endif
