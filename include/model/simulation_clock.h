#ifndef CLOCK_H
#define CLOCK_H

class AbsoluteTime;
class TimeDifference;
class TimePassageSpeed;

#include "controller/realtime_clock.h"


class TimeDifference
{
    friend class AbsoluteTime;
    friend class RealTimeDifference;
private:
    long long nano_seconds;

public:
    TimeDifference(long long);
    const AbsoluteTime operator+(const AbsoluteTime&) const;
    const RealTimeDifference operator/(const TimePassageSpeed&) const;
    const TimePassageSpeed operator/(const RealTimeDifference&) const;
    bool operator==(const TimeDifference&) const;
    bool operator!=(const TimeDifference&) const;
    bool operator>(const TimeDifference&) const;
};


class AbsoluteTime
{
    friend class SimulationClock;
    friend class TimeDifference;
private:
    unsigned long long nano_seconds;

public:
    AbsoluteTime(unsigned long long);
    const TimeDifference operator-(const AbsoluteTime&) const;
    bool operator==(const AbsoluteTime&) const;
    bool operator!=(const AbsoluteTime&) const;
    bool operator>(const AbsoluteTime&) const;
    bool operator>=(const AbsoluteTime&) const;

};


class TimePassageSpeed
{
friend class RealTimeDifference;
private:
    float speed;

public:
    TimePassageSpeed(float);
    float get_time_passage_spped() const;
    const TimePassageSpeed operator*(const TimePassageSpeed&) const;
    const TimeDifference operator*(const RealTimeDifference&) const;
};


class SimulationClock
{
private:
    AbsoluteTime simulation_time;
    RealTime real_time;
    TimePassageSpeed time_passage_speed;
    bool turned_on;

public:
    SimulationClock(const AbsoluteTime&, const RealTime&);
    void start(const RealTime&);
    void stop(const RealTime&);
    void scale_time_passage(const TimePassageSpeed&);
    const AbsoluteTime now(const RealTime&);
    bool is_turned_on();
};

#endif
