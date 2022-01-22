#ifndef MINECRAFT_CHUNKHEAP_H
#define MINECRAFT_CHUNKHEAP_H

#include "../headers/includes.h"

#include "Chunk.h"

class ChunkHeap {

public:

    uint mWidth, mHeight, mLength;
    std::vector<Chunk> mChunks;

    static void normalizeCoords(int& chX, int& chY, int& chZ, int& x, int& y, int& z);

    ChunkHeap(uint width, uint height, uint length);

    uint getWidth() const;
    uint getHeight() const;
    uint getLength() const;

    Chunk& chunk(int x, int y, int z);
    Chunk& chunk(const glm::vec3& pos);
    const Chunk& getChunk(int x, int y, int z) const;
    const Chunk& getChunk(const glm::vec3& pos) const;
    void setChunk(int x, int y, int z, Chunk chunk);
    void setChunk(const glm::vec3& pos, Chunk chunk);

    bool chunkExists(int chX, int chY, int chZ) const;
    bool voxelExists(int chX, int chY, int chZ, int x, int y, int z) const;
    const Voxel& getVoxel(int chX, int chY, int chZ, int x, int y, int z) const;
    bool voxelNotNull(int chX, int chY, int chZ, int x, int y, int z) const;
};

#endif //MINECRAFT_CHUNKHEAP_H