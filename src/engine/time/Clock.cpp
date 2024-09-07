#include <engine/time/Clock.h>

timespec currentTime() {
    timespec curTime { 0, 0 };
    clock_gettime(CLOCK_MONOTONIC, &curTime);
    return curTime;
}

timespec operator+(const timespec& start, const timespec& stop) {
    timespec result { stop.tv_sec + start.tv_sec, stop.tv_nsec + start.tv_nsec };
    if (result.tv_nsec > 1000000000L) {
        result.tv_sec += 1;
        result.tv_nsec -= 1000000000L;
    }
    return result;
}

timespec operator-(const timespec& start, const timespec& stop) {
    timespec result { stop.tv_sec - start.tv_sec, stop.tv_nsec - start.tv_nsec };
    if (result.tv_nsec < 0) {
        result.tv_sec -= 1;
        result.tv_nsec += 1000000000L;
    }
    return result;
}

Clock::Clock() {
    start();
}

void Clock::start() {
    mTime = currentTime();
    mIsPaused = false;
}

void Clock::restart() {
    start();
}

void Clock::pause() {
    if (mIsPaused)
        return;
    timespec curTime = currentTime();
    mTime = mTime + curTime;
    mIsPaused = true;
}

void Clock::resume() {
    if (!mIsPaused)
        return;
    timespec curTime = currentTime();
    mTime = mTime - curTime;
    mIsPaused = false;
}

long Clock::elapsedSeconds(bool refresh) {
    return elapsedNanos(refresh) / 1000000000L;
}

long Clock::elapsedMillis(bool refresh) {
    return elapsedNanos(refresh) / 1000000L;
}

long Clock::elapsedMicros(bool refresh) {
    return elapsedNanos(refresh) / 1000L;
}

long Clock::elapsedNanos(bool refresh) {
    timespec curTime = currentTime();
    timespec elapsedTime = curTime - mTime;
    if (refresh)
        mTime = curTime;
    return elapsedTime.tv_sec * 1000000000L + elapsedTime.tv_nsec;
}

float Clock::elapsedSecondsF(bool refresh) {
    return static_cast<float>(elapsedNanos(refresh)) / 1000000000.0f;
}

double Clock::elapsedSecondsD(bool refresh) {
    return static_cast<double>(elapsedNanos(refresh)) / 1000000000.0;
}