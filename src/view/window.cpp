#include <GLFW/glfw3.h>

#include "view/window.h"


Window::Window(const char* name, int width, int height)
{
    this->window_handle = glfwCreateWindow(width, height, name, nullptr, nullptr);
    if (!this->window_handle)
    {
        glfwTerminate();
        std::exit(2);
    }
}

Window::~Window()
{
    glfwDestroyWindow(this->window_handle);
}

void Window::show()
{
    glfwMakeContextCurrent(this->window_handle);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(this->window_handle))
    {
        int width, height;
        glfwGetFramebufferSize(this->window_handle, &width, &height);

        glClear( GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        this->draw(width, height);
        glfwPollEvents();
        glfwSwapBuffers(this->window_handle);
    }
}

MainWindow::MainWindow(const char* name, int width, int height)
    : Window(name, width, height)
{

}

void MainWindow::draw(int width, int height)
{

}
