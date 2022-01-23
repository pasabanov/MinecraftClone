#ifndef MINECRAFT_CHUNKHEAP_H
#define MINECRAFT_CHUNKHEAP_H

#include "../../headers/includes.h"

#include "Chunk.h"

class ChunkHeap {

    uint mWidth, mHeight, mLength;
    std::vector<Chunk> mChunks;

    bool voxelExists0(int chX, int chY, int chZ, int x, int y, int z) const;
    bool voxelNotNull0(int chX, int chY, int chZ, int x, int y, int z) const;

public:

    static void normalizeCoords(int& chX, int& chY, int& chZ, int& x, int& y, int& z);

    ChunkHeap(uint width, uint height, uint length);

    uint getWidth() const;
    uint getHeight() const;
    uint getLength() const;
    uint getVolume() const;

    Chunk& getChunk(int x, int y, int z);
    Chunk& getChunk(const glm::vec3& pos);
    const Chunk& getChunk(int x, int y, int z) const;
    const Chunk& getChunk(const glm::vec3& pos) const;
    void setChunk(int x, int y, int z, Chunk chunk);
    void setChunk(const glm::vec3& pos, Chunk chunk);

    bool chunkExists(int chX, int chY, int chZ) const;

    bool voxelExists(int chX, int chY, int chZ, int x, int y, int z) const;
    bool voxelNotNull(int chX, int chY, int chZ, int x, int y, int z) const;

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
};

#endif //MINECRAFT_CHUNKHEAP_H