#ifndef VIEW_H
#define VIEW_H

#include <thread>

#include "controller/event_queue.hpp"
#include "window.h"


class View
{
private:
    EventQueue* const event_queue;
    std::unique_ptr<Window> main_window;
    std::unique_ptr<std::thread> main_window_thread;

public:
    View(EventQueue * const);
    void start();
    void join();
    ~View();
};

#endif
