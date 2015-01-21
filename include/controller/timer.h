#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
  template <class callable, class... arguments>
  Timer(const RealTime &time, bool async, callable&& f, arguments&&... args)
  {
    std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
    std::thread([time, task]() {
        std::this_thread::sleep_for((time - RealTime::now()).get_duration());
        task();
      }).detach();
  }

};

#endif /* TIMER_H */
