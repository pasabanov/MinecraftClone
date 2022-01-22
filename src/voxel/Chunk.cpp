#include "Chunk.h"



bool Chunk::voxelExists(int x, int y, int z) {
    return x >= 0 && x < Chunk::WIDTH && y >= 0 && y < Chunk::HEIGHT && z >= 0 && z < Chunk::LENGTH;
}



Chunk::Chunk(const VoxelGenerator& generator) : mVoxels(VOLUME) {
    generateVoxels(generator);
}



void Chunk::generateVoxels(const VoxelGenerator& generator) {
    if (generator == nullptr)
        return;
    for (uint y = 0; y < HEIGHT; ++y)
        for (uint z = 0; z < LENGTH; ++z)
            for (uint x = 0; x < WIDTH; ++x)
                setVoxel(x, y, z, generator(x, y, z));
}



Voxel& Chunk::voxel(uint x, uint y, uint z) {
    return mVoxels[(y * LENGTH + z) * WIDTH + x];
}

Voxel& Chunk::voxel(const glm::vec3& pos) {
    return voxel(pos.x, pos.y, pos.z);
}



const Voxel& Chunk::getVoxel(uint x, uint y, uint z) const {
    return mVoxels[(y * LENGTH + z) * WIDTH + x];
}

const Voxel& Chunk::getVoxel(const glm::vec3& pos) {
    return getVoxel(pos.x, pos.y, pos.z);
}



void Chunk::setVoxel(uint x, uint y, uint z, const Voxel& voxel) {
    mVoxels[(y * LENGTH + z) * WIDTH + x] = voxel;
}

void Chunk::setVoxel(const glm::vec3& pos, const Voxel& voxel) {
    setVoxel(pos.x, pos.y, pos.z, voxel);
}