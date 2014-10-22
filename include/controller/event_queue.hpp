#include <queue>
#include <mutex>
#include <condition_variable>

#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

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
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable condition;

public:
    void push(T const &item)
    {
        std::unique_lock<std::mutex> mlock(mutex);
        queue.push(item);
        mlock.unlock();
        condition.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        while (queue.empty())
        {
            condition.wait(mlock);
        }
        auto item = queue.front();
        queue.pop();
        return item;
    }
};

typedef BlockingQueue<Event*> EventQueue;

#endif
