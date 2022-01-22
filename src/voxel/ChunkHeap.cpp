#include "ChunkHeap.h"



void ChunkHeap::normalizeCoords(int& chX, int& chY, int& chZ, int& x, int& y, int& z) {
    while (x < 0) {
        --chX;
        x += Chunk::WIDTH;
    }
    while (x >= Chunk::WIDTH) {
        ++chX;
        x -= Chunk::WIDTH;
    }
    while (y < 0) {
        --chY;
        y += Chunk::HEIGHT;
    }
    while (y >= Chunk::HEIGHT) {
        ++chY;
        y -= Chunk::HEIGHT;
    }
    while (z < 0) {
        --chZ;
        z += Chunk::LENGTH;
    }
    while (z >= Chunk::LENGTH) {
        ++chZ;
        z -= Chunk::LENGTH;
    }
}



ChunkHeap::ChunkHeap(uint width, uint height, uint length)
: mWidth(width), mHeight(height), mLength(length), mChunks(0) {
    uint volume = width * height * length;
    mChunks.resize(volume);
    for (int y = 0; y < height; ++y) {
        for (int z = 0; z < length; ++z) {
            for (int x = 0; x < width; ++x) {
                setChunk(x, y, z, Chunk(
                        [](uint x, uint y, uint z) {
                            int id = y <= (sin(x*0.6) * 0.5 + 0.5) * 10;
                            if (y <= 2 && id != 0)
                                id = 2;
                            return Voxel(id);
                        }
                ));
            }
        }
    }
}



uint ChunkHeap::getWidth() const {
    return mWidth;
}

uint ChunkHeap::getHeight() const {
    return mHeight;
}

uint ChunkHeap::getLength() const {
    return mLength;
}



Chunk& ChunkHeap::chunk(int x, int y, int z) {
    return mChunks[(y * mLength + z) * mWidth + x];
}

Chunk& ChunkHeap::chunk(const glm::vec3& pos) {
    return chunk(pos.x, pos.y, pos.z);
}



const Chunk& ChunkHeap::getChunk(int x, int y, int z) const {
    return mChunks[(y * mLength + z) * mWidth + x];
}

const Chunk& ChunkHeap::getChunk(const glm::vec3& pos) const {
    return getChunk(pos.x, pos.y, pos.z);
}



void ChunkHeap::setChunk(int x, int y, int z, Chunk chunk) {
    mChunks[(y * mLength + z) * mWidth + x] = chunk;
}

void ChunkHeap::setChunk(const glm::vec3& pos, Chunk chunk) {
    setChunk(pos.x, pos.y, pos.z, chunk);
}



bool ChunkHeap::chunkExists(int chX, int chY, int chZ) const {
    return chX >= 0 && chX < mWidth && chY >= 0 && chY < mHeight && chZ >= 0 && chZ < mLength;
}

bool ChunkHeap::voxelExists(int chX, int chY, int chZ, int x, int y, int z) const {
    normalizeCoords(chX, chY, chZ, x, y, z);
    if (!chunkExists(chX, chY, chZ))
        return false;
    return Chunk::voxelExists(x, y, z);
}

const Voxel& ChunkHeap::getVoxel(int chX, int chY, int chZ, int x, int y, int z) const {
    normalizeCoords(chX, chY, chZ, x, y, z);
    return getChunk(chX, chY, chZ).getVoxel(x, y, z);
}

bool ChunkHeap::voxelNotNull(int chX, int chY, int chZ, int x, int y, int z) const {
    normalizeCoords(chX, chY, chZ, x, y, z);
    if (!voxelExists(chX, chY, chZ, x, y, z))
        return false;
    return getVoxel(chX, chY, chZ, x, y, z).getId() != 0;
}