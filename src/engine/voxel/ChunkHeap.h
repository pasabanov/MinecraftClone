#pragma once

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