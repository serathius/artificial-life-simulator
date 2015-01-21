#ifndef REALTIME_CLOCK_H
#define	REALTIME_CLOCK_H

#include <chrono>
#include <iostream>

class TimeDifference;
class TimePassageSpeed;
class RealTime;


class RealTimeDifference
{
public:
  typedef std::chrono::steady_clock::duration Duration;
  explicit RealTimeDifference(const Duration&);
  bool operator==(const RealTimeDifference&) const;
  bool operator!=(const RealTimeDifference&) const;
  bool operator>(const RealTimeDifference&) const;
  friend std::ostream& operator<<(std::ostream &os,
  const RealTimeDifference &realtime);
  const Duration get_duration() const;
  const TimeDifference operator*(const TimePassageSpeed&) const;
  const RealTime operator+(const RealTime&) const;


private:
    Duration duration;
};


class RealTime
{
  friend class RealTimeDifference;
public:
  typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
  RealTime(const TimePoint&);
  static const RealTime now();
  bool operator==(const RealTime&) const;
  bool operator!=(const RealTime&) const;
  bool operator>(const RealTime&) const;
  bool operator>=(const RealTime&) const;
  friend std::ostream& operator<<(std::ostream &os, const RealTime &realtime);
  const RealTimeDifference operator-(const RealTime&) const;
  void schedule() const;

private:
  TimePoint time_point;

};

#include "model/simulation_clock.h"

#endif	/* REALTIME_CLOCK_H */

