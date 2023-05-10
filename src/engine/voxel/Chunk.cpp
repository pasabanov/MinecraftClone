#include <engine/voxel/Chunk.h>



bool Chunk::voxelExists(int x, int y, int z) {
    return x >= 0 && x < Chunk::WIDTH && y >= 0 && y < Chunk::HEIGHT && z >= 0 && z < Chunk::LENGTH;
}



Chunk::Chunk(int x, int y, int z, const VoxelGenerator& generator) : mX(x), mY(y), mZ(z), mVoxels(VOLUME) {
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



int Chunk::getX() const {
    return mX;
}

int Chunk::getY() const {
    return mY;
}

int Chunk::getZ() const {
    return mZ;
}

void Chunk::setX(int x) {
    mX = x;
}

void Chunk::setY(int y) {
    mY = y;
}

void Chunk::setZ(int z) {
    mZ = z;
}



Voxel& Chunk::getVoxel(uint x, uint y, uint z) {
    return mVoxels[(y * LENGTH + z) * WIDTH + x];
}

const Voxel& Chunk::getVoxel(uint x, uint y, uint z) const {
    return mVoxels[(y * LENGTH + z) * WIDTH + x];
}

void Chunk::setVoxel(uint x, uint y, uint z, const Voxel& voxel) {
    mVoxels[(y * LENGTH + z) * WIDTH + x] = voxel;
    setModified(true);
}



ubyte Chunk::getLight(int x, int y, int z, int channel) const {
    if (voxelExists(x, y, z))
        return mLightMap.get(x, y, z, channel);
    return 0;
}

void Chunk::setLight(int x, int y, int z, int channel, int value) {
    if (voxelExists(x, y, z)) {
        mLightMap.set(x, y, z, channel, value);
        setModified(true);
    }
}


bool Chunk::isModified() const {
    return mModified;
}

void Chunk::setModified(bool modified) {
    mModified = modified;
}



Voxel& Chunk::getVoxel(int index) {
    return mVoxels[index];
}

const Voxel& Chunk::getVoxel(int index) const {
    return mVoxels[index];
}

void Chunk::setVoxel(int index, const Voxel& voxel) {
    mVoxels[index] = voxel;
}