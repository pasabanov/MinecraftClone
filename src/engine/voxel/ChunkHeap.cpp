#include "ChunkHeap.h"



void ChunkHeap::normalizeCoords(int& chX, int& chY, int& chZ, int& x, int& y, int& z) {
    chX += x / Chunk::WIDTH;
    x %= Chunk::WIDTH;
    chY += y / Chunk::HEIGHT;
    y %= Chunk::HEIGHT;
    chZ += z / Chunk::LENGTH;
    z %= Chunk::LENGTH;
    if (x < 0) {
        --chX;
        x += Chunk::WIDTH;
    }
    if (y < 0) {
        --chY;
        y += Chunk::HEIGHT;
    }
    if (z < 0) {
        --chZ;
        z += Chunk::LENGTH;
    }
}



ChunkHeap::ChunkHeap(uint width, uint height, uint length)
: mWidth(width), mHeight(height), mLength(length), mChunks(0) {
    uint volume = width * height * length;
    mChunks.resize(volume);
    for (int y = 0; y < height; ++y) {
        for (int z = 0; z < length; ++z) {
            for (int x = 0; x < width; ++x) {
                setChunk(x, y, z, Chunk(x, y, z,
                        [&](uint vx, uint vy, uint vz) {
                            int realX = vx + x * Chunk::WIDTH;
                            int realY = vy + y * Chunk::HEIGHT;
                            int realZ = vz + z * Chunk::LENGTH;
                            // 1
//                            float height = glm::perlin(glm::vec3(realX*0.05, realZ*0.05, 0));
//                            int id = realY <= std::max(height * 10.0 + 5.0, 2.0);
//                            if (realY <= 2 && id != 0)
//                                id = 2;
                            // 2
//                            int id = glm::perlin(glm::vec3(realX*0.0125f,realY*0.0125f, realZ*0.0125f)) > 0.1f;//*/real_y <= (height) * 60 + 30;
//                            if (realY <= 2 && id != 0)
//                                id = 2;
                            // 3
                            int id = vy <= ((sin(vx * 0.6) + cos(vz * 0.4)) * 0.5 + 0.5) * 10;
                            if (vy <= 2 && id != 0)
                                id = 2;
                            // 4
//                            int id = vy <= 6 ? vy <= 2 ? vy >= 1 ? 2 : 0 : 1 : 0;
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

uint ChunkHeap::getVolume() const {
    return mChunks.size();
}



Chunk& ChunkHeap::getChunk(int x, int y, int z) {
    return mChunks[(y * mLength + z) * mWidth + x];
}

const Chunk& ChunkHeap::getChunk(int x, int y, int z) const {
    return mChunks[(y * mLength + z) * mWidth + x];
}

void ChunkHeap::setChunk(int x, int y, int z, const Chunk& chunk) {
    mChunks[(y * mLength + z) * mWidth + x] = chunk;
}



Chunk* ChunkHeap::getChunkPtrByVoxel(int x, int y, int z) {
    int chX = 0, chY = 0, chZ = 0;
    normalizeCoords(chX, chY, chZ, x, y, z);
    if (chunkExists(chX, chY, chZ))
        return &getChunk(chX, chY, chZ);
    return nullptr;
}



uchar ChunkHeap::getLight(int x, int y, int z, int channel) const {
    int chX = 0, chY = 0, chZ = 0;
    normalizeCoords(chX, chY, chZ, x, y, z);
    if (chunkExists(chX, chY, chZ))
        return getChunk(chX, chY, chZ).getLight(x, y, z, channel);
    return 0;
}

uchar ChunkHeap::getLight(int chX, int chY, int chZ, int x, int y, int z, int channel) const {
    normalizeCoords(chX, chY, chZ, x, y, z);
    if (chunkExists(chX, chY, chZ))
        return getChunk(chX, chY, chZ).getLight(x, y, z, channel);
    return 0;
}

void ChunkHeap::setLight(int x, int y, int z, int channel, int value) {
    int chX = 0, chY = 0, chZ = 0;
    normalizeCoords(chX, chY, chZ, x, y, z);
    if (chunkExists(chX, chY, chZ))
        getChunk(chX, chY, chZ).setLight(x, y, z, channel, value);

    if (x == 0)
        if (chunkExists(chX - 1, chY, chZ))
            getChunk(chX - 1, chY, chZ).setModified(true);
    if (x == Chunk::WIDTH - 1)
        if (chunkExists(chX + 1, chY, chZ))
            getChunk(chX + 1, chY, chZ).setModified(true);
    if (y == 0)
        if (chunkExists(chX, chY - 1, chZ))
            getChunk(chX, chY - 1, chZ).setModified(true);
    if (y == Chunk::HEIGHT - 1)
        if (chunkExists(chX, chY + 1, chZ))
            getChunk(chX, chY + 1, chZ).setModified(true);
    if (z == 0)
        if (chunkExists(chX, chY, chZ - 1))
            getChunk(chX, chY, chZ - 1).setModified(true);
    if (z == Chunk::LENGTH - 1)
        if (chunkExists(chX, chY, chZ + 1))
            getChunk(chX, chY, chZ + 1).setModified(true);
}



bool ChunkHeap::chunkExists(int chX, int chY, int chZ) const {
    return chX >= 0 && chX < mWidth && chY >= 0 && chY < mHeight && chZ >= 0 && chZ < mLength;
}



bool ChunkHeap::voxelExists(int chX, int chY, int chZ, int x, int y, int z) const {
    normalizeCoords(chX, chY, chZ, x, y, z);
    return voxelExists_safe(chX, chY, chZ, x, y, z);
}

bool ChunkHeap::voxelExists_safe(int chX, int chY, int chZ, int x, int y, int z) const {
    return chunkExists(chX, chY, chZ) && Chunk::voxelExists(x, y, z);
}

bool ChunkHeap::voxelNotNull(int chX, int chY, int chZ, int x, int y, int z) const {
    normalizeCoords(chX, chY, chZ, x, y, z);
    return voxelNotNull_safe(chX, chY, chZ, x, y, z);
}

bool ChunkHeap::voxelNotNull_safe(int chX, int chY, int chZ, int x, int y, int z) const {
    return voxelExists_safe(chX, chY, chZ, x, y, z) && getChunk(chX, chY, chZ).getVoxel(x, y, z).getId() != 0;
}



Voxel& ChunkHeap::getVoxelGlobal(int x, int y, int z) {
    int chX = 0, chY = 0, chZ = 0;
    normalizeCoords(chX, chY, chZ, x, y, z);
    return getChunk(chX, chY, chZ).getVoxel(x, y, z);
}

const Voxel& ChunkHeap::getVoxelGlobal(int x, int y, int z) const {
    int chX = 0, chY = 0, chZ = 0;
    normalizeCoords(chX, chY, chZ, x, y, z);
    return getChunk(chX, chY, chZ).getVoxel(x, y, z);
}

void ChunkHeap::setVoxelGlobal(int x, int y, int z, const Voxel& newVoxel) {

    int chX = 0, chY = 0, chZ = 0;
    normalizeCoords(chX, chY, chZ, x, y, z);

    if (!voxelExists_safe(chX, chY, chZ, x, y, z))
        return;

    Chunk& chunk = getChunk(chX, chY, chZ);

    Voxel& voxel = chunk.getVoxel(x, y, z);

    if (voxel == newVoxel)
        return;

    voxel = newVoxel;

    chunk.setModified(true);

    if (x == 0)
        if (chunkExists(chX - 1, chY, chZ))
            getChunk(chX - 1, chY, chZ).setModified(true);
    if (x == Chunk::WIDTH - 1)
        if (chunkExists(chX + 1, chY, chZ))
            getChunk(chX + 1, chY, chZ).setModified(true);
    if (y == 0)
        if (chunkExists(chX, chY - 1, chZ))
            getChunk(chX, chY - 1, chZ).setModified(true);
    if (y == Chunk::HEIGHT - 1)
        if (chunkExists(chX, chY + 1, chZ))
            getChunk(chX, chY + 1, chZ).setModified(true);
    if (z == 0)
        if (chunkExists(chX, chY, chZ - 1))
            getChunk(chX, chY, chZ - 1).setModified(true);
    if (z == Chunk::LENGTH - 1)
        if (chunkExists(chX, chY, chZ + 1))
            getChunk(chX, chY, chZ + 1).setModified(true);
}



Voxel* ChunkHeap::rayCast(
        const glm::vec3& a,
        const glm::vec3& dir,
        float maxDist,
        glm::vec3& end,
        glm::vec3& norm,
        glm::vec3& iend) {

    static const float infinity = std::numeric_limits<float>::infinity();

    float px = a.x;
    float py = a.y;
    float pz = a.z;

    float dx = dir.x;
    float dy = dir.y;
    float dz = dir.z;

    int ix = std::floor(px);
    int iy = std::floor(py);
    int iz = std::floor(pz);

    float stepx = (dx > 0) ? 1 : -1;
    float stepy = (dy > 0) ? 1 : -1;
    float stepz = (dz > 0) ? 1 : -1;

    float txDelta = (dx == 0) ? infinity : std::abs(1 / dx);
    float tyDelta = (dy == 0) ? infinity : std::abs(1 / dy);
    float tzDelta = (dz == 0) ? infinity : std::abs(1 / dz);

    float xdist = (stepx > 0) ? (ix + 1 - px) : (px - ix);
    float ydist = (stepy > 0) ? (iy + 1 - py) : (py - iy);
    float zdist = (stepz > 0) ? (iz + 1 - pz) : (pz - iz);

    float txMax = (txDelta < infinity) ? txDelta * xdist : infinity;
    float tyMax = (tyDelta < infinity) ? tyDelta * ydist : infinity;
    float tzMax = (tzDelta < infinity) ? tzDelta * zdist : infinity;

    float t = 0;

    int steppedIndex = -1;

    while (t <= maxDist) {

        int vX = ix, vY = iy, vZ = iz;
        int cX = 0, cY = 0, cZ = 0;
        normalizeCoords(cX, cY, cZ, vX, vY, vZ);

        Voxel* voxel = voxelExists_safe(cX, cY, cZ, vX, vY, vZ)
                ? &getChunk(cX, cY, cZ).getVoxel(vX, vY, vZ)
                : nullptr;

        if (voxel != nullptr && voxel->getId() != 0) {
            end.x = px + t * dx;
            end.y = py + t * dy;
            end.z = pz + t * dz;

            iend.x = ix;
            iend.y = iy;
            iend.z = iz;

            norm.x = norm.y = norm.z = 0;
            if (steppedIndex == 0)
                norm.x = -stepx;
            if (steppedIndex == 1)
                norm.y = -stepy;
            if (steppedIndex == 2)
                norm.z = -stepz;
            return voxel;
        }

        if (txMax < tyMax) {
            if (txMax < tzMax) {
                ix += stepx;
                t = txMax;
                txMax += txDelta;
                steppedIndex = 0;
            } else {
                iz += stepz;
                t = tzMax;
                tzMax += tzDelta;
                steppedIndex = 2;
            }
        } else {
            if (tyMax < tzMax) {
                iy += stepy;
                t = tyMax;
                tyMax += tyDelta;
                steppedIndex = 1;
            } else {
                iz += stepz;
                t = tzMax;
                tzMax += tzDelta;
                steppedIndex = 2;
            }
        }
    }

    iend.x = ix;
    iend.y = iy;
    iend.z = iz;

    end.x = px + t * dx;
    end.y = py + t * dy;
    end.z = pz + t * dz;
    norm.x = norm.y = norm.z = 0;

    return nullptr;
}



int ChunkHeap::coordsToIndex(int x, int y, int z) const {
    return (y * mLength + z) * mWidth + x;
}



Chunk& ChunkHeap::getChunk(int index) {
    return mChunks[index];
}

const Chunk& ChunkHeap::getChunk(int index) const {
    return mChunks[index];
}

void ChunkHeap::setChunk(int index, const Chunk& chunk) {
    mChunks[index] = chunk;
}