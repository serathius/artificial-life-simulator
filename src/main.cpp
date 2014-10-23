#include "view/view.h"

int main(int argc, char** argv)
{
    std::unique_ptr<EventQueue> queue =
        std::unique_ptr<EventQueue>(new EventQueue);
    std::unique_ptr<View> view = std::unique_ptr<View>(new View(queue.get()));
    view->start();
    view->join();
    return 0;
}
