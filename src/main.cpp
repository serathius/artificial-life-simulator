#include <iostream>
#include "controller/controller.cpp"
#include "controller/blocking_queue.cpp"
#include "controller/events.cpp"

using namespace std;


int main()
{
    BlockingQueue<Event*>* queue = new BlockingQueue<Event*>();
    queue->push(new StringEvent("asd"));
    queue->push(new StringEvent("asdasdasdas"));
    queue->push(new StringEvent("asdasdasdas"));


    Controller* con = new Controller(queue);
    con->handle_events();
    return 0;
}

