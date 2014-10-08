#include <queue>
#include <mutex>
#include <condition_variable>

#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

template<typename T>
class BlockingQueue
{
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable condition;

public:
    void push(T const& value);
    T pop();
};

#endif