#include <queue>
#include <mutex>
#include <condition_variable>

#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

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
    void push(T const& item);
    T pop();
};

#endif