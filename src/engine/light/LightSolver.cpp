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

#include <engine/light/LightSolver.h>

LightSolver::LightSolver(ChunkHeap* mChunks, int mChannel) : mChunks(mChunks), mChannel(mChannel) {}

void LightSolver::add(int x, int y, int z) {
	add(x, y, z, mChunks->getLight(x, y, z, mChannel));
}

void LightSolver::add(int x, int y, int z, int emission) {

	if (emission <= 1)
		return;

	mAddQueue.push({ x, y, z, (uchar) emission });

	mChunks->setLight(x, y, z, mChannel, emission);
}

void LightSolver::remove(int x, int y, int z) {

	if (mChunks->getChunkPtrByVoxel(x, y, z) == nullptr)
		return;

	int light = mChunks->getLight(x, y, z, mChannel);
	if (light == 0)
		return;

	mRemQueue.push({ x, y, z, (uchar) light });

	mChunks->setLight(x, y, z, mChannel, 0);
}

void LightSolver::solve() {

	static const int coords[] = {
			0, 0, 1,
			0, 0,-1,
			0, 1, 0,
			0,-1, 0,
			1, 0, 0,
			-1, 0, 0
	};

	while (!mRemQueue.empty()) {

		LightEntry entry = mRemQueue.front();
		mRemQueue.pop();

		for (size_t i = 0; i < 6; ++i) {

			int x = entry.x + coords[i*3 + 0];
			int y = entry.y + coords[i*3 + 1];
			int z = entry.z + coords[i*3 + 2];

			Chunk* chunk = mChunks->getChunkPtrByVoxel(x, y, z);

			if (chunk) {

				int light = mChunks->getLight(x, y, z, mChannel);

				if (light != 0 && light == entry.light - 1) {
					mRemQueue.push({ x, y, z, (uchar) light });
					mChunks->setLight(x, y, z, mChannel, 0);
				} else if (light >= entry.light) {
					mAddQueue.push({ x, y, z, (uchar) light });
				}
			}
		}
	}

	while (!mAddQueue.empty()) {

		LightEntry entry = mAddQueue.front();
		mAddQueue.pop();

		if (entry.light <= 1)
			continue;

		for (size_t i = 0; i < 6; ++i) {

			int x = entry.x + coords[i*3 + 0];
			int y = entry.y + coords[i*3 + 1];
			int z = entry.z + coords[i*3 + 2];

			Chunk* chunk = mChunks->getChunkPtrByVoxel(x, y, z);

			if (chunk) {

				int light = mChunks->getLight(x, y, z, mChannel);

				Voxel& v = mChunks->getVoxelGlobal(x, y, z);

				if (v.getId() == 0 && light < entry.light - 1) {
					mChunks->setLight(x, y, z, mChannel, entry.light - 1);
					mAddQueue.push({ x, y, z, (uchar) (entry.light - 1) });
				}
			}
		}
	}
}