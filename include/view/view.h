#ifndef VIEW_H
#define VIEW_H

class View;

#include <thread>
#include <memory>

#include "controller/event_queue.hpp"
#include "window.h"
#include "view/viewmodel.h"

class View
{
private:
  EventQueue* const event_queue;
  std::unique_ptr<MainWindow> main_window;
  std::unique_ptr<std::thread> main_window_thread;

public:
  View(EventQueue * const);
  void update(const ViewModel& viewmodel_);
  void start();
  void finish();
  ~View();
};

#endif
