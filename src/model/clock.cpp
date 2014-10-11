#include <cassert>

#include "model/clock.h"


SimulationClock::SimulationClock(const AbsoluteTime& time, const TimePassageSpeed& simulation_speed)
: simulation_time(time), real_time(RealTime::now()),
  time_passage_speed(simulation_speed), turned_on(false)
{
}

void SimulationClock::start()
{
    assert(this->turned_on == false);
    this->real_time = RealTime::now();
    this->turned_on = true;
}

void SimulationClock::stop()
{
    assert(this->turned_on == true);
    auto real_time_now = RealTime::now();
    auto real_time_passed = real_time_now - this->real_time;
    this->real_time = real_time_now;
    this->simulation_time = (real_time_passed * this->time_passage_speed +
        this->simulation_time);
    this->turned_on = false;
}

void SimulationClock::scale_time_passage(const TimePassageSpeed& scale)
{
    if (this->turned_on)
    {
        this->stop();
        this->time_passage_speed = this->time_passage_speed * scale;
        this->start();
    }
    else
        this->time_passage_speed = this->time_passage_speed * scale;
}

const AbsoluteTime SimulationClock::now()
{
    if(this->turned_on)
    {
        auto real_time_passed = RealTime::now() - this->real_time;
        return (real_time_passed * this->time_passage_speed +
                this->simulation_time);
    }
    else
    {
        return this->simulation_time;
    }
}

bool SimulationClock::is_turned_on()
{
    return this->turned_on;
}

AbsoluteTime::AbsoluteTime(unsigned long long nano_seconds)
{
    this->nano_seconds = nano_seconds;
}

bool AbsoluteTime::operator==(const AbsoluteTime& other) const
{
    return this->nano_seconds == other.nano_seconds;
}

bool AbsoluteTime::operator!=(const AbsoluteTime& other) const
{
    return this->nano_seconds != other.nano_seconds;
}

bool AbsoluteTime::operator>(const AbsoluteTime& other) const
{
    return this->nano_seconds > other.nano_seconds;
}

const TimeDifference AbsoluteTime::operator-(const AbsoluteTime& other) const
{
    return TimeDifference(this->nano_seconds - other.nano_seconds);
}

TimeDifference::TimeDifference(long long nano_seconds)
{
    this->nano_seconds = nano_seconds;
};

const AbsoluteTime TimeDifference::operator+(
    const AbsoluteTime& absolute_time) const
{
    long long absolute_nanoseconds = (absolute_time.nano_seconds +
        this->nano_seconds);
    assert(absolute_nanoseconds >= 0);
    return AbsoluteTime(absolute_nanoseconds);
}

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

bool TimeDifference::operator==(const TimeDifference& other) const
{
    return this->nano_seconds == other.nano_seconds;
}

TimePassageSpeed::TimePassageSpeed(float speed)
{
    assert(speed > 0);
    this->speed = speed;
}

const TimePassageSpeed TimePassageSpeed::operator*(
    const TimePassageSpeed& other) const
{
    return TimePassageSpeed(this->speed * other.speed);
}
