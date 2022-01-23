#ifndef MINECRAFT_CLOCK_H
#define MINECRAFT_CLOCK_H

#include "../../headers/includes.h"

timespec operator-(const timespec& start, const timespec& stop);

class Clock {

    timespec mTime;

public:

    Clock();

    void start();
    void restart();

    void pause();
    void resume();

    long elapsedTimeSecond();
    long elapsedTimeMillis();
    long elapsedTimeMicros();
    long elapsedTimeNanos();
};

#endif //MINECRAFT_CLOCK_H