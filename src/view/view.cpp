#include "view/view.h"


View::View(EventQueue * const event_queue) : event_queue(event_queue)
{
    if(!glfwInit())
        std::exit(1);
}

void View::start()
{
    this->main_window = std::unique_ptr<MainWindow>(
        new MainWindow("Artificial Life Simulator", 500, 500));
    this->main_window_thread = std::unique_ptr<std::thread>(
        new std::thread(&MainWindow::show, this->main_window.get()));
}

void View::finish()
{
    this->main_window_thread->join();
}


View::~View()
{
    if(this->main_window_thread->joinable())
    {
        this->main_window_thread->join();
    }
    glfwTerminate();
}

void View::update(const ViewModel& viewmodel_)
{
    main_window->viewmodel_ = viewmodel_;
}
