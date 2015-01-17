#ifndef WINDOW_H_
#define WINDOW_H_

#include <cstdlib>

#include <GLFW/glfw3.h>

#include "view/viewmodel.h"


class Window
{
private:
    GLFWwindow* window_handle_;
    virtual void draw(int, int) = 0;

public:
	Window(const char*, int, int);
    virtual ~Window();
    void show();
};


class MainWindow : public Window
{
private:
    virtual void draw(int, int);

public:
    ViewModel viewmodel_;
    MainWindow(const char *, int, int);
};

#endif /* WINDOW_H_ */
