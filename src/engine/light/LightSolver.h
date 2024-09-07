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

#include <engine/voxel/ChunkHeap.h>

class LightEntry {
public:
	int x, y, z;
	uchar light;
};

class LightSolver {

	std::queue<LightEntry> mAddQueue, mRemQueue;
	ChunkHeap* mChunks;
	int mChannel;

public:

	LightSolver(ChunkHeap* chunks, int channel);

	void add(int x, int y, int z);

	void add(int x, int y, int z, int emission);

	void remove(int x, int y, int z);

	void solve();
};