#include <cassert>

#include "model/simulation_clock.h"


SimulationClock::SimulationClock(const AbsoluteTime& simulation_time,
    const RealTime& realtime) : simulation_time(simulation_time),
        realtime(realtime), time_passage_speed(TimePassageSpeed(1.0)),
        turned_on(false)
{

}

void SimulationClock::start(const RealTime& realtime)
{
    assert(this->turned_on == false);
    this->realtime = realtime;
    this->turned_on = true;
}

void SimulationClock::stop(const RealTime& realtime)
{
    assert(this->turned_on == true);
    assert(realtime >= this->realtime);
    auto time_passed = realtime - this->realtime;
    this->realtime = realtime;
    this->simulation_time = (time_passed * this->time_passage_speed +
        this->simulation_time);
    this->turned_on = false;
}

void SimulationClock::scale_time_passage(const TimePassageSpeed& scale)
{
    assert(this->turned_on == false);
    this->time_passage_speed = this->time_passage_speed * scale;
}

const AbsoluteTime SimulationClock::to_simulation_time(const RealTime& realtime)
{
    assert(realtime >= this->realtime);
    if(this->turned_on)
    {
        auto time_passed = realtime - this->realtime;
        return time_passed * this->time_passage_speed + this->simulation_time;
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


float TimePassageSpeed::get_time_passage_speed() const
{
    return this->speed;
}
