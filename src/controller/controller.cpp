#include <typeindex>
#include <iostream>
#include <utility>

#include "controller/controller.h"
#include "common.h"

Controller::Controller() : view_(&event_queue_)
{

}

void Controller::start()
{
  view_.start();
  model_.create_new_game(RealTime::now());
  handle_events();
  view_.finish();
}

void Controller::handle_events()
{
  while(run_)
  {
    view_.update(model_.get_viewmodel());
    schedule_model_update();
    Event* event = event_queue_.pop();
    LOG("Handle Event");
    event->accept(this);
    model_.update(event->get_time());
    delete event;
  }
}

void Controller::schedule_model_update()
{
  try
  {
    RealTime time = model_.get_next_event_time();
    std::thread([time, this]() {
      auto time_difference = time - RealTime::now();
      LOG(time_difference);
      std::this_thread::sleep_for(time_difference.get_duration());
      event_queue_.push(new UpdateModelEvent(time));
    }).detach();
  } catch(InfiniteRealTime)
  {

  }
}

void Controller::visit(UpdateModelEvent *event)
{
  LOG("Model Update");
}

void Controller::visit(ExitEvent * exit_event)
{
  run_=false;
}
