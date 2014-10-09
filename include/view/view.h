#ifndef VIEW_H
#define VIEW_H

#include "controller/blocking_queue.h"

class View
{
private:
    typedef BlockingQueue<Event*> EventQueue;
    EventQueue* const event_queue;
public:
    View(EventQueue * const);
};

#endif