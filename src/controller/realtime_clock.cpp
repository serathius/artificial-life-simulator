#include "controller/realtime_clock.h"


RealTime::RealTime(const RealTime::TimePoint &time_point)
{
  this->time_point_ = time_point;
}

const RealTimeDifference RealTime::operator-(const RealTime &other) const
{
  return RealTimeDifference(this->time_point_ - other.time_point_);
}

bool RealTimeDifference::operator==(const RealTimeDifference &other) const
{
  return this->duration_ == other.duration_;
}

RealTimeDifference::RealTimeDifference(
  const RealTimeDifference::Duration &duration)
{
  this->duration_ = duration;
}

std::ostream& operator<<(std::ostream &os,
  const RealTimeDifference &realtime)
{
  os << "RealTimeDifference(" << std::chrono::duration_cast<
    std::chrono::nanoseconds>(realtime.duration_).count() / 1000000000.f
    << "s)";
  return os;
}

bool RealTime::operator>(const RealTime& other) const
{
  return this->time_point_ > other.time_point_;
}

bool RealTime::operator>=(const RealTime& other) const
{
  return this->time_point_ >= other.time_point_;
}

const TimeDifference RealTimeDifference::operator*(
  const TimePassageSpeed& passage) const
{
  auto duration_in_nanoseconds = (
    std::chrono::duration_cast<std::chrono::nanoseconds>(
      this->duration_).count());
  return TimeDifference(duration_in_nanoseconds * passage);
}

const RealTime RealTimeDifference::operator+(const RealTime& other) const
{
  return RealTime(this->duration_ + other.time_point_);
}

bool RealTime::operator== (const RealTime& other) const
{
  return this->time_point_ == other.time_point_;
}

const RealTime RealTime::now()
{
  return RealTime(std::chrono::steady_clock::now());
}

const RealTimeDifference::Duration RealTimeDifference::get_duration() const
{
  return duration_;
}

std::ostream& operator<<(std::ostream &os, const RealTime &realtime)
{
  os << "RealTime(" << realtime.time_point_.time_since_epoch().count() << ")";
  return os;
}
