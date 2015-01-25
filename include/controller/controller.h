#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unordered_map>

class Controller;

#include "view/view.h"
#include "controller/event_queue.hpp"
#include "model/model.h"


class Controller
{
public:
  Controller();
  void start();
  void visit(UpdateModelEvent* event);
  void visit(ExitEvent* exit_event);

private:
  void handle_events();
  void schedule_model_update();

  bool run_ = true;
  Model model_;
  View view_;
  EventQueue event_queue_;
};

#endif /* CONTROLLER_H */
