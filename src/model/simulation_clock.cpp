#include <cassert>

#include "model/simulation_clock.h"


SimulationClock::SimulationClock(const AbsoluteTime &simulation_time)
  : simulation_time_(simulation_time),
    realtime_(RealTime::TimePoint(std::chrono::seconds(0))),
    time_passage_speed_(TimePassageSpeed(1.0)), turned_on_(false)
{

}

void SimulationClock::start(const RealTime &realtime)
{
  assert(turned_on_ == false);
  realtime_ = realtime;
  turned_on_ = true;
}

void SimulationClock::stop(const RealTime &realtime)
{
  assert(turned_on_ == true);
  assert(realtime >= realtime_);
  auto time_passed = realtime - realtime_;
  realtime_ = realtime;
  simulation_time_ = (time_passed * time_passage_speed_ +
    simulation_time_);
  turned_on_ = false;
}

void SimulationClock::scale_time_passage(const TimePassageSpeed& scale)
{
  assert(turned_on_ == false);
  time_passage_speed_ = time_passage_speed_ * scale;
}

const AbsoluteTime SimulationClock::to_simulation_time(const RealTime &realtime)
{
  assert(realtime >= realtime_);
  if(turned_on_)
  {
    auto time_passed = realtime - realtime_;
    return time_passed * time_passage_speed_ + simulation_time_;
  }
  else
  {
    return simulation_time_;
  }
}

const RealTime SimulationClock::to_realtime(const AbsoluteTime &actual_time)
{
  assert(actual_time >= simulation_time_);
  if(turned_on_)
  {
    auto time_difference = actual_time - simulation_time_;
    return time_difference / time_passage_speed_ + realtime_;
  }
  else
    throw InfiniteRealTime();
}

bool SimulationClock::is_turned_on()
{
  return turned_on_;
}

AbsoluteTime::AbsoluteTime(unsigned long long nano_seconds)
{
  nano_seconds_ = nano_seconds;
}

bool AbsoluteTime::operator==(const AbsoluteTime &other) const
{
  return nano_seconds_ == other.nano_seconds_;
}

bool AbsoluteTime::operator!=(const AbsoluteTime &other) const
{
  return nano_seconds_ != other.nano_seconds_;
}

bool AbsoluteTime::operator>(const AbsoluteTime &other) const
{
  return nano_seconds_ > other.nano_seconds_;
}

const TimeDifference AbsoluteTime::operator-(const AbsoluteTime &other) const
{
  return TimeDifference(nano_seconds_ - other.nano_seconds_);
}

TimeDifference::TimeDifference(long long nano_seconds)
{
  nano_seconds_ = nano_seconds;
};

const TimeDifference TimeDifference::seconds(float seconds)
{
  return TimeDifference((long long)(seconds * 1000000000));
};

const AbsoluteTime TimeDifference::operator+(
  const AbsoluteTime &absolute_time) const
{
  long long absolute_nanoseconds = (absolute_time.nano_seconds_ +
    nano_seconds_);
  assert(absolute_nanoseconds >= 0);
  return AbsoluteTime(absolute_nanoseconds);
}

bool TimeDifference::operator==(const TimeDifference &other) const
{
  return nano_seconds_ == other.nano_seconds_;
}

TimePassageSpeed::TimePassageSpeed(float speed)
{
  assert(speed > 0);
  speed_thousandth_ = speed * 1000;
}

long long operator/(long long value,
  const TimePassageSpeed &time_passage_speed)
{
  return value * 1000 / time_passage_speed.speed_thousandth_;
}

long long operator*(long int value,
  const TimePassageSpeed &time_passage_speed)
{
  return value * time_passage_speed.speed_thousandth_ / 1000;
}

const TimePassageSpeed TimePassageSpeed::operator*(
  const TimePassageSpeed &other) const
{
  return TimePassageSpeed(speed_thousandth_ * other.speed_thousandth_ / 1000);
}

bool AbsoluteTime::operator >=(const AbsoluteTime &other) const
{
  return nano_seconds_ >= other.nano_seconds_;
}

const RealTimeDifference TimeDifference::operator/(
  const TimePassageSpeed &time_passage_speed) const
{
  unsigned long long nanoseconds_passed = (nano_seconds_ / time_passage_speed);
  RealTimeDifference::Duration realtime_passed =
    std::chrono::nanoseconds(nanoseconds_passed);
  return RealTimeDifference(realtime_passed);
}

const AbsoluteTime AbsoluteTime::operator+(const TimeDifference &difference) const
{
  return AbsoluteTime(nano_seconds_ + difference.nano_seconds_);
}

std::ostream& operator<<(std::ostream &os, const AbsoluteTime &simulation_time)
{
  os << "AbsoluteTime(" << simulation_time.nano_seconds_ << ")";
  return os;
}
