#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
private:
    Model* const model;
    View* const view;
    typedef BlockingQueue<Event*> EventQueue;
    EventQueue* const event_queue;

    class ControllerStrategy
    {
        void react(Event * const);
    };

    class PrintStrategy: public ControllerStrategy
    {
        void react(Event * const);
    };
public:
    Controller(Model* const, View* const, EventQueue* const);
    void handle_events();
};

#endif