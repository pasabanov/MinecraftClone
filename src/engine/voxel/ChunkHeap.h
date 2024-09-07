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

#include <engine/voxel/Chunk.h>

class ChunkHeap {

	uint mWidth, mHeight, mLength;
	std::vector<Chunk> mChunks;

public:

	static void normalizeCoords(int& chX, int& chY, int& chZ, int& x, int& y, int& z);

	ChunkHeap(uint vx, uint vy, uint vz);

	uint getWidth() const;
	uint getHeight() const;
	uint getLength() const;
	uint getVolume() const;

	Chunk& getChunk(int x, int y, int z);
	const Chunk& getChunk(int x, int y, int z) const;
	void setChunk(int x, int y, int z, const Chunk& chunk);

	Chunk* getChunkPtrByVoxel(int x, int y, int z);

	uchar getLight(int x, int y, int z, int channel) const;
	uchar getLight(int chX, int chY, int chZ, int x, int y, int z, int channel) const;
	void setLight(int x, int y, int z, int channel, int value);

	bool chunkExists(int chX, int chY, int chZ) const;

	bool voxelExists(int chX, int chY, int chZ, int x, int y, int z) const;
	bool voxelExists_safe(int chX, int chY, int chZ, int x, int y, int z) const;
	bool voxelNotNull(int chX, int chY, int chZ, int x, int y, int z) const;
	bool voxelNotNull_safe(int chX, int chY, int chZ, int x, int y, int z) const;

	Voxel& getVoxelGlobal(int x, int y, int z);
	const Voxel& getVoxelGlobal(int x, int y, int z) const;
	void setVoxelGlobal(int x, int y, int z, const Voxel& newVoxel);

	Voxel* rayCast(
			const glm::vec3& a,
			const glm::vec3& dir,
			float maxDist,
			glm::vec3& end,
			glm::vec3& norm,
			glm::vec3& iend);

	int coordsToIndex(int x, int y, int z) const;

	Chunk& getChunk(int index);
	const Chunk& getChunk(int index) const;
	void setChunk(int index, const Chunk& chunk);
};