#include "controller/realtime_clock.h"

RealTime::RealTime(const RealTime::TimePoint& time_point)
{
    this->time_point = time_point;
}

const RealTime RealTime::now()
{
    return RealTime(std::chrono::steady_clock::now());
}

const RealTimeDifference RealTime::operator-(const RealTime& other) const
{
    return RealTimeDifference(this->time_point - other.time_point);
}

bool RealTimeDifference::operator==(const RealTimeDifference& other) const
{
    return this->duration == other.duration;
}

RealTimeDifference::RealTimeDifference(
    const RealTimeDifference::Duration& duration)
{
    this->duration = duration;
}

const TimeDifference RealTimeDifference::operator*(
    const TimePassageSpeed& passage) const
{
    auto duration_in_nanoseconds = (
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            this->duration).count());
    return TimeDifference(duration_in_nanoseconds * passage.speed);
}