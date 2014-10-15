#include "gtest/gtest.h"
#include "model/simulation_clock.h"

TEST (SimulationClockTest, test_on_new_clock)
{
    SimulationClock clock(AbsoluteTime(0), TimePassageSpeed(1.0));
    ASSERT_EQ(clock.now(), AbsoluteTime(0));
}

TEST (SimulationClockTest, test_now_on_started_clock)
{
    SimulationClock clock(AbsoluteTime(0), TimePassageSpeed(1.0));
    clock.start();
    ASSERT_GT(clock.now(), AbsoluteTime(0));
}

TEST (SimulationClockTest, test_now_stopped_clock)
{
    SimulationClock clock(AbsoluteTime(0), TimePassageSpeed(1.0));
    clock.start();
    clock.stop();
    auto then = clock.now();
    1 + 1;
    ASSERT_EQ(clock.now(), then);
}

TEST(SimulationClockTest, test_new_clock_is_not_turned_on)
{
    SimulationClock clock(AbsoluteTime(0), TimePassageSpeed(1.0));
    ASSERT_FALSE(clock.is_turned_on());
}

TEST(SimulationClockTest, test_is_turned_on)
{
    SimulationClock clock(AbsoluteTime(0), TimePassageSpeed(1.0));
    clock.start();
    ASSERT_TRUE(clock.is_turned_on());
}

TEST(SimulationClockTest, test_is_turned_off)
{
    SimulationClock clock(AbsoluteTime(0), TimePassageSpeed(1.0));
    clock.start();
    clock.stop();
    ASSERT_FALSE(clock.is_turned_on());
}

TEST (TimePassageSpeedTest, test_assert_positive_time_passage)
{
    ASSERT_DEATH(TimePassageSpeed(-1.0), "");
}

TEST (TimeDifferenceTest, test_time_difference)
{
    RealTimeDifference difference(std::chrono::seconds(1));
    TimePassageSpeed passage_speed(1.0);
    ASSERT_EQ(TimeDifference(1000000000), difference * passage_speed);
}

TEST (TimePassageSpeedTest, test_time_passsage)
{
    RealTimeDifference difference(std::chrono::seconds(1));
    TimePassageSpeed passage_speed(1.234);
    ASSERT_EQ(TimeDifference(1234000000), difference * passage_speed);
}

TEST(SimulationClockTest, test_assert_on_double_start)
{
    SimulationClock clock(AbsoluteTime(0), TimePassageSpeed(1.0));
    clock.start();
    ASSERT_DEATH(clock.start(), "");
}

TEST(RealTimeDifferenceTest, test_difference)
{
    RealTime start(RealTime::TimePoint(std::chrono::seconds(1)));
    RealTime stop(RealTime::TimePoint(std::chrono::seconds(2)));
    ASSERT_EQ(RealTimeDifference(std::chrono::seconds(1)), stop-start);
}

TEST(TimeTest, test_time_operators)
{
    TimeDifference a(1);
    AbsoluteTime b(1);
    ASSERT_EQ(AbsoluteTime(2), a + b);
}

TEST(AbsoluteTime, test_assert_positive_time)
{
    ASSERT_DEATH(TimeDifference(-1) + AbsoluteTime(0), "");
}
