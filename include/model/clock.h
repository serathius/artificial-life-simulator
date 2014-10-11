#include<chrono>

#ifndef CLOCK_H
#define CLOCK_H

class AbsoluteTime;
class TimeDifference;
class TimePassageSpeed;

class RealTimeDifference
{
public:
    typedef std::chrono::steady_clock::duration Duration;
private:
    Duration duration;

public:
    explicit RealTimeDifference(const Duration&);
    const TimeDifference operator*(const TimePassageSpeed&) const;
    bool operator==(const RealTimeDifference&) const;
};


class RealTime
{
public:
    typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
private:
    TimePoint time_point;
public:
    explicit RealTime(const TimePoint&);
    static const RealTime now();
    const RealTimeDifference operator-(const RealTime&) const;
};


class TimeDifference
{
    friend class AbsoluteTime;
    friend class RealTimeDifference;
private:
    long long nano_seconds;

public:
    TimeDifference(long long);
    const AbsoluteTime operator+(const AbsoluteTime&) const;
    bool operator==(const TimeDifference&) const;
};


class AbsoluteTime
{
    friend class Clock;
    friend class TimeDifference;
private:
    unsigned long long nano_seconds;

public:
    AbsoluteTime(unsigned long long);
    const TimeDifference operator-(const AbsoluteTime&) const;
    bool operator==(const AbsoluteTime&) const;
    bool operator!=(const AbsoluteTime&) const;
    bool operator>(const AbsoluteTime&) const;
};


class TimePassageSpeed
{
friend class RealTimeDifference;
private:
    float speed;

public:
    TimePassageSpeed(float);
    const TimePassageSpeed operator*(const TimePassageSpeed&) const;
};


class Clock
{
private:
    AbsoluteTime simulation_time;
    RealTime real_time;
    TimePassageSpeed time_passage_speed;
    bool turned_on;

public:
    Clock(const AbsoluteTime&, const TimePassageSpeed&);
    void start();
    void stop();
    void scale_time_passage(const TimePassageSpeed&);
    const AbsoluteTime now();
    bool is_turned_on();
};

#endif
