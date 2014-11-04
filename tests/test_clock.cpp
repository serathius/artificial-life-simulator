#include "gtest/gtest.h"
#include "model/simulation_clock.h"

TEST (SimulationClockTest, test_on_new_clock)
{
    RealTime::TimePoint time_point;
    SimulationClock clock(AbsoluteTime(0), RealTime(time_point));
    ASSERT_EQ(clock.to_simulation_time(RealTime(time_point)), AbsoluteTime(0));
}

TEST (SimulationClockTest, test_to_simulation_time_assert_time)
{
    SimulationClock clock(AbsoluteTime(0),
        RealTime(RealTime::TimePoint(std::chrono::seconds(1))));
    ASSERT_DEATH(clock.to_simulation_time(
        RealTime(RealTime::TimePoint(std::chrono::seconds(0)))), "");
}

TEST (SimulationClockTest, test_stop_assert_time)
{
    SimulationClock clock(AbsoluteTime(0),
        RealTime(RealTime::TimePoint(std::chrono::seconds(1))));
    ASSERT_DEATH(
        clock.stop(RealTime(RealTime::TimePoint(std::chrono::seconds(0)))), "");
}

TEST (SimulationClockTest, test_to_simulation_time_on_started_clock)
{
    SimulationClock clock(AbsoluteTime(0), RealTime(RealTime::TimePoint()));
    clock.start(RealTime(RealTime::TimePoint(std::chrono::seconds(0))));
    ASSERT_EQ(
        clock.to_simulation_time(RealTime(
            RealTime::TimePoint(std::chrono::seconds(1)))),
        AbsoluteTime(1000000000));
}

TEST (SimulationClockTest, test_to_simulation_time_stopped_clock)
{
    SimulationClock clock(AbsoluteTime(0), RealTime(RealTime::TimePoint()));
    clock.start(RealTime(RealTime::TimePoint()));
    clock.stop(RealTime(RealTime::TimePoint(std::chrono::seconds(1))));
    ASSERT_EQ(
        clock.to_simulation_time(
            RealTime(RealTime::TimePoint(std::chrono::seconds(1)))),
        AbsoluteTime(1000000000));
}

TEST(SimulationClockTest, test_new_clock_is_not_turned_on)
{
    SimulationClock clock(AbsoluteTime(0), RealTime(RealTime::TimePoint()));
    ASSERT_FALSE(clock.is_turned_on());
}

TEST(SimulationClockTest, test_is_turned_on)
{
    SimulationClock clock(AbsoluteTime(0), RealTime(RealTime::TimePoint()));
    clock.start(RealTime(RealTime::TimePoint()));
    ASSERT_TRUE(clock.is_turned_on());
}

TEST(SimulationClockTest, test_is_turned_off)
{
    SimulationClock clock(AbsoluteTime(0), RealTime(RealTime::TimePoint()));
    clock.start(RealTime(RealTime::TimePoint()));
    clock.stop(RealTime(RealTime::TimePoint()));
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
    SimulationClock clock(AbsoluteTime(0), RealTime(RealTime::TimePoint()));
    clock.start(RealTime(RealTime::TimePoint()));
    ASSERT_DEATH(clock.start(RealTime(RealTime::TimePoint())), "");
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

TEST(RealTimeTest, test_real_time_gt1)
{
    RealTime start = RealTime(RealTime::TimePoint(std::chrono::seconds(1)));
    RealTime stop = RealTime(RealTime::TimePoint(std::chrono::seconds(2)));
    ASSERT_TRUE(stop > start);
}

TEST(RealTimeTest, test_real_time_gt2)
{
    RealTime start = RealTime(RealTime::TimePoint(std::chrono::seconds(1)));
    RealTime stop = RealTime(RealTime::TimePoint(std::chrono::seconds(1)));
    ASSERT_FALSE(stop > start);
}

TEST(RealTimeTest, test_real_time_gt3)
{
    RealTime start = RealTime(RealTime::TimePoint(std::chrono::seconds(2)));
    RealTime stop = RealTime(RealTime::TimePoint(std::chrono::seconds(1)));
    ASSERT_FALSE(stop > start);
}

TEST(RealTimeTest, test_real_time_ge1)
{
    RealTime start = RealTime(RealTime::TimePoint(std::chrono::seconds(1)));
    RealTime stop = RealTime(RealTime::TimePoint(std::chrono::seconds(2)));
    ASSERT_TRUE(stop >= start);
}

TEST(RealTimeTest, test_real_time_ge2)
{
    RealTime start = RealTime(RealTime::TimePoint(std::chrono::seconds(1)));
    RealTime stop = RealTime(RealTime::TimePoint(std::chrono::seconds(1)));
    ASSERT_TRUE(stop >= start);
}

TEST(RealTimeTest, test_real_time_ge3)
{
    RealTime start = RealTime(RealTime::TimePoint(std::chrono::seconds(2)));
    RealTime stop = RealTime(RealTime::TimePoint(std::chrono::seconds(1)));
    ASSERT_FALSE(stop >= start);
}

TEST(RealTimeDifferenceTest, test_add_realtime)
{
    RealTimeDifference time_passed(
        RealTimeDifference::Duration(std::chrono::seconds(1)));
    RealTime begin = RealTime(RealTime::TimePoint(std::chrono::seconds(1)));
    RealTime end = time_passed + begin;
    ASSERT_EQ(end, RealTime(RealTime::TimePoint(std::chrono::seconds(2))));
}

TEST(AbsoluteTimeTest, test_gte1)
{
    AbsoluteTime lesser(1);
    AbsoluteTime bigger(2);
    ASSERT_TRUE(bigger >= lesser);
}

TEST(AbsoluteTimeTest, test_gte2)
{
    AbsoluteTime first(1);
    AbsoluteTime second(1);
    ASSERT_TRUE(first >= second);
}

TEST(AbsoluteTimeTest, test_gte3)
{
    AbsoluteTime lesser(1);
    AbsoluteTime bigger(2);
    ASSERT_FALSE(lesser >= bigger);
}
