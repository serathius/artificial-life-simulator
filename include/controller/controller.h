#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

class Controller;

#include "view/view.h"
#include "controller/event_queue.hpp"
#include "model/model.h"



class Controller
{
private:
    Model model_;
    View view_;
    EventQueue event_queue_;

    void handle_events();
    void schedule_model_update();

public:
    Controller();
    void start();
    void visit(UpdateModelEvent* event);
};
#endif
