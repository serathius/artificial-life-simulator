#ifndef CLOCK_H
#define CLOCK_H

#include <exception>
#include <iostream>

class AbsoluteTime;
class TimeDifference;
class TimePassageSpeed;

#include "controller/realtime_clock.h"


class TimeDifference
{
  friend class AbsoluteTime;
  friend class RealTimeDifference;
public:
  static const TimeDifference seconds(float seconds);
  bool operator==(const TimeDifference&) const;
  bool operator!=(const TimeDifference&) const;
  bool operator>(const TimeDifference&) const;
  const AbsoluteTime operator+(const AbsoluteTime&) const;
  const RealTimeDifference operator/(const TimePassageSpeed&) const;
  float get_seconds() const;

private:
  long long nano_seconds_;

  TimeDifference(long long nanoseconds);

};


class AbsoluteTime
{
    friend class SimulationClock;
    friend class TimeDifference;
public:
  AbsoluteTime(unsigned long long nanoseconds);
  static const AbsoluteTime get_max();
  friend std::ostream& operator<<(std::ostream&, const AbsoluteTime&);
  const TimeDifference operator-(const AbsoluteTime&) const;
  const AbsoluteTime operator+(const TimeDifference&) const;
  bool operator==(const AbsoluteTime&) const;
  bool operator!=(const AbsoluteTime&) const;
  bool operator>(const AbsoluteTime&) const;
  bool operator>=(const AbsoluteTime&) const;
private:
    unsigned long long nano_seconds_;
};


class TimePassageSpeed
{
friend class RealTimeDifference;

private:
    unsigned int speed_thousandth_;

public:
  TimePassageSpeed(float);
  friend long long operator/(long long, const TimePassageSpeed&);
  friend long long operator*(long int, const TimePassageSpeed&);
  const TimePassageSpeed operator*(const TimePassageSpeed&) const;
  const TimeDifference operator*(const RealTimeDifference&) const;
};


class SimulationClock
{
private:
  AbsoluteTime simulation_time_;
  RealTime realtime_;
  TimePassageSpeed time_passage_speed_;
  bool turned_on_;

public:
  SimulationClock(const AbsoluteTime&);
  void start(const RealTime&);
  void stop(const RealTime&);
  void scale_time_passage(const TimePassageSpeed&);
  const AbsoluteTime to_simulation_time(const RealTime&);
  const RealTime to_realtime(const AbsoluteTime&);
  bool is_turned_on();
};

class InfiniteRealTime : public std::exception
{
};
#endif
