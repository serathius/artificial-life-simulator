#include "gtest/gtest.h"
#include "model/simulation_clock.h"

TEST (SimulationClockTest, test_on_new_clock)
{
    RealTime::TimePoint time_point;
    SimulationClock clock(AbsoluteTime(0));
    ASSERT_EQ(clock.to_simulation_time(RealTime(time_point)), AbsoluteTime(0));
}

TEST (SimulationClockTest, test_to_simulation_time_on_started_clock)
{
    SimulationClock clock(AbsoluteTime(0));
    clock.start(RealTime(RealTime::TimePoint(std::chrono::seconds(0))));
    ASSERT_EQ(
        clock.to_simulation_time(RealTime(
            RealTime::TimePoint(std::chrono::seconds(1)))),
        AbsoluteTime(1000000000));
}

TEST (SimulationClockTest, test_to_simulation_time_stopped_clock)
{
    SimulationClock clock(AbsoluteTime(0));
    clock.start(RealTime(RealTime::TimePoint()));
    clock.stop(RealTime(RealTime::TimePoint(std::chrono::seconds(1))));
    ASSERT_EQ(
        clock.to_simulation_time(
            RealTime(RealTime::TimePoint(std::chrono::seconds(1)))),
        AbsoluteTime(1000000000));
}

TEST(SimulationClockTest, test_new_clock_is_not_turned_on)
{
    SimulationClock clock(AbsoluteTime(0));
    ASSERT_FALSE(clock.is_turned_on());
}

TEST(SimulationClockTest, test_is_turned_on)
{
    SimulationClock clock(AbsoluteTime(0));
    clock.start(RealTime(RealTime::TimePoint()));
    ASSERT_TRUE(clock.is_turned_on());
}

TEST(SimulationClockTest, test_is_turned_off)
{
    SimulationClock clock(AbsoluteTime(0));
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
    ASSERT_EQ(TimeDifference::seconds(1), difference * passage_speed);
}

TEST (TimePassageSpeedTest, test_time_passsage)
{
    RealTimeDifference difference(std::chrono::seconds(1));
    TimePassageSpeed passage_speed(1.234);
    ASSERT_EQ(TimeDifference::seconds(1.234), difference * passage_speed);
}

TEST(SimulationClockTest, test_assert_on_double_start)
{
    SimulationClock clock(AbsoluteTime(0));
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
    TimeDifference a = TimeDifference::seconds(1);
    AbsoluteTime b(1000000000);
    ASSERT_EQ(AbsoluteTime(2000000000), a + b);
}

TEST(AbsoluteTime, test_assert_positive_time)
{
    ASSERT_DEATH(TimeDifference::seconds(-1) + AbsoluteTime(0), "");
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

TEST(TimeDifferenceTest, test_dividing_by_time_passage)
{
    TimeDifference simulation_time_passed = TimeDifference::seconds(2);
    TimePassageSpeed time_passage_speed(2.0);
    RealTimeDifference realtime_passed = (
        simulation_time_passed / time_passage_speed);
    ASSERT_EQ(RealTimeDifference(RealTimeDifference::Duration(
            std::chrono::seconds(1))), realtime_passed);
}

TEST(SimulationClockTest, test_to_realtime_asserts_time_didnt_shift)
{
    AbsoluteTime simulation_start(1);
    RealTime realtime_start(RealTime::TimePoint(std::chrono::seconds(1)));
    SimulationClock clock(simulation_start);
    ASSERT_DEATH(clock.to_realtime(AbsoluteTime(0)), "");
}


TEST(SimulationClockTest, test_to_realtime_throws_when_clock_stopped)
{
    AbsoluteTime simulation_start(1);
    SimulationClock clock(simulation_start);
    ASSERT_THROW(clock.to_realtime(AbsoluteTime(1)), InfiniteRealTime);
}

TEST(SimulationClockTest, test_to_realtime)
{
    AbsoluteTime simulation_start(0);
    RealTime realtime_start(RealTime::TimePoint(std::chrono::seconds(0)));
    SimulationClock clock(simulation_start);
    clock.start(realtime_start);
    ASSERT_EQ(RealTime(RealTime::TimePoint(std::chrono::nanoseconds(1))),
        clock.to_realtime(AbsoluteTime(1)));
}
