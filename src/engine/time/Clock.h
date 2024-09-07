#pragma once

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

#include <headers/includes.h>

class Clock {

	timespec mTime;
	bool mIsPaused = false;

public:

	Clock();

	void start();
	void restart();

	void pause();
	void resume();

	long elapsedSeconds(bool refresh = true);
	long elapsedMillis(bool refresh = true);
	long elapsedMicros(bool refresh = true);
	long elapsedNanos(bool refresh = true);

	float elapsedSecondsF(bool refresh = true);
	double elapsedSecondsD(bool refresh = true);
};