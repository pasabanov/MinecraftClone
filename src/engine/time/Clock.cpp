/*
 * MinecraftClone
 * Copyright (C) © 2022  Petr Alexandrovich Sabanov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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