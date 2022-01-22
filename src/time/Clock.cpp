#include "Clock.h"



timespec operator-(const timespec& start, const timespec& stop) {
    timespec result { stop.tv_sec - start.tv_sec, stop.tv_nsec - start.tv_nsec };
    if (stop.tv_nsec - start.tv_nsec < 0) {
        result.tv_sec -= 1;
        result.tv_nsec += 1000000000L;
    }
    return result;
}



Clock::Clock() {
    start();
}



void Clock::start() {
    mTime.tv_sec = mTime.tv_nsec = 0;
    clock_gettime(CLOCK_MONOTONIC, &mTime);
}



void Clock::restart() {
    start();
}



void Clock::pause() {
    // do nothing
}



void Clock::resume() {
    start();
}



long Clock::elapsedTimeSecond() {
    return elapsedTimeNanos() / 1000000000L;
}



long Clock::elapsedTimeMillis() {
    return elapsedTimeNanos() / 1000000L;
}



long Clock::elapsedTimeMicros() {
    return elapsedTimeNanos() / 1000L;
}



long Clock::elapsedTimeNanos() {
    timespec curTime { 0, 0 };
    clock_gettime(CLOCK_MONOTONIC, &curTime);
    timespec elapsedTime = curTime - mTime;
    mTime = curTime;
    return elapsedTime.tv_sec * 1000000000L + elapsedTime.tv_nsec;
}