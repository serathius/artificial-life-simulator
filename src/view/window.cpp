#include <GLFW/glfw3.h>

#include "view/window.h"
#include "view/view.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  reinterpret_cast<Window*>(
    glfwGetWindowUserPointer(window))->handle_key_event(key);
}

void window_close_callback(GLFWwindow* window)
{
  reinterpret_cast<Window*>(
    glfwGetWindowUserPointer(window))->handle_window_close();
}

void Window::handle_key_event(int key)
{
  if(key == GLFW_KEY_ESCAPE)
  {
    event_queue_->push(new ExitEvent(RealTime::now()));
  }
}

void Window::handle_window_close()
{
  event_queue_->push(new ExitEvent(RealTime::now()));
}

Window::Window(const char* name, int width, int height, EventQueue* event_queue)
{
  this->event_queue_ = event_queue;
  window_handle_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
  glfwSetWindowUserPointer(window_handle_, this);
  glfwSetKeyCallback(window_handle_, key_callback);
  glfwSetWindowCloseCallback(window_handle_, window_close_callback);

  if (!window_handle_)
  {
    glfwTerminate();
    std::exit(2);
  }
}

Window::~Window()
{
  glfwDestroyWindow(window_handle_);
}

void MainWindow::set_viewmodel(const ViewModel &viewmodel)
{
  std::unique_lock<std::mutex> mlock(mutex_);
  viewmodel_ = viewmodel;
}

void Window::show()
{
  glfwMakeContextCurrent(window_handle_);
  glfwSwapInterval(1);
  while (!glfwWindowShouldClose(window_handle_))
  {
    int width, height;
    glfwGetFramebufferSize(window_handle_, &width, &height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    this->draw(width, height);

    glfwSwapBuffers(window_handle_);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
  }
}

void Window::close()
{
  glfwSetWindowShouldClose(window_handle_, GL_TRUE);
}

MainWindow::MainWindow(const char* name, int width, int height, EventQueue* event_queue)
  : Window(name, width, height, event_queue)
{
}

void MainWindow::draw(int width, int height) {
  std::unique_lock<std::mutex> mlock(mutex_);
  viewmodel_.draw();
  mlock.unlock();
}
