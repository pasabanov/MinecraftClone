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

class LightMap {

	std::vector<short> mMap;

public:

	LightMap();

	ubyte get(int x, int y, int z, int channel) const;
	ubyte getR(int x, int y, int z) const;
	ubyte getG(int x, int y, int z) const;
	ubyte getB(int x, int y, int z) const;
	ubyte getS(int x, int y, int z) const;

	void set(int x, int y, int z, int channel, int value);
	void setR(int x, int y, int z, int value);
	void setG(int x, int y, int z, int value);
	void setB(int x, int y, int z, int value);
	void setS(int x, int y, int z, int value);
};