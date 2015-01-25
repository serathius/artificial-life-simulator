#ifndef WINDOW_H_
#define WINDOW_H_

#include <cstdlib>
#include <mutex>

#include <GLFW/glfw3.h>

#include "view/viewmodel.h"
#include "controller/event_queue.hpp"


class Window
{
private:
  GLFWwindow* window_handle_;
  EventQueue* event_queue_;
  virtual void draw(int, int) = 0;

public:
  Window(const char*, int, int, EventQueue*);
  virtual ~Window();
  void show();
  void close();
  void handle_key_event(int key);
  void handle_window_close();
};


class MainWindow : public Window
{
private:
  virtual void draw(int, int);
  ViewModel viewmodel_;
  std::mutex mutex_;

public:
  void set_viewmodel(const ViewModel&);
  MainWindow(const char *, int, int, EventQueue*);

};

#endif /* WINDOW_H_ */
