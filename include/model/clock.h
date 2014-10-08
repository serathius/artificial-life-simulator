#include<chrono>

#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
private:
    AbsoluteTime* simulation_time;
    RealTime* real_time;
    float passage_of_time;
    
public:
    void start();
    void stop();
    void speed_up_passage_of_time(float);
    const AbsoluteTime& now();
};

class RealTime
{
private:
    std::chrono::time_point<std::chrono::steady_clock> time_point;

    
};

class AbsoluteTime
{
friend Clock;
private:
    AbsoluteTime();

public:
    const TimeDifferece& operator-(const AbsoluteTime&) const;
};

class TimeDifferece
{
friend AbsoluteTime;
private:
    TimeDifferece();

public:
    const AbsoluteTime& operator+(const AbsoluteTime&) const;
};

#endif