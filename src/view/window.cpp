#include <GLFW/glfw3.h>

#include "view/window.h"


Window::Window(const char* name, int width, int height)
{
    window_handle_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
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

void Window::show()
{
    glfwMakeContextCurrent(window_handle_);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window_handle_))
    {
        int width, height;
        glfwGetFramebufferSize(window_handle_, &width, &height);

        glClear( GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        this->draw(width, height);
        glfwPollEvents();
        glfwSwapBuffers(window_handle_);
    }
}

MainWindow::MainWindow(const char* name, int width, int height)
    : Window(name, width, height)
{

}

void MainWindow::draw(int width, int height) {
    std::unique_lock<std::mutex> mlock(mutex);
    viewmodel_.draw();
    mlock.unlock();
    float a = 0.1;
    glColor3f(1.f, 1.f, 1.f);
    glBegin(GL_TRIANGLES);
      glVertex2f(0.f, 0.f);
      glVertex2f(0.f, a);
      glVertex2f(a, a);
      glVertex2f(0.f, 0.f);
      glVertex2f(a, 0.f);
      glVertex2f(a, -a);
      glVertex2f(0.f, 0.f);
      glVertex2f(0.f, -a);
      glVertex2f(-a, -a);
      glVertex2f(0.f, 0.f);
      glVertex2f(-a, 0.f);
      glVertex2f(-a, a);
    glEnd();

}
