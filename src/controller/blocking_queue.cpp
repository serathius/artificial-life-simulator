#include "controller/blocking_queue.h"

template<typename T>
void BlockingQueue<T>::push(T const &item)
{
    std::unique_lock<std::mutex> mlock(mutex);
    queue.push(item);
    mlock.unlock();
    condition.notify_one();
}

template<typename T>
T BlockingQueue<T>::pop()
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
