#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

template<typename T>
class BlockingQueue;
class Event;

typedef BlockingQueue<Event*> EventQueue;

#include "events.h"

/*
--------------------WARNING-------------------
this code don't have unit tests, but it's tested
do not modify this unless you run your own tests
--------------------WARNING-------------------
 */

template<typename T>
class BlockingQueue
{
public:
  void push(T const &item)
  {
	  std::unique_lock<std::mutex> mlock(mutex_);
      queue_.push(item);
      mlock.unlock();
      condition_.notify_one();
  }

  T pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
        condition_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    return item;
  }

private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable condition_;

};

#endif /* EVENT_QUEUE_H */
