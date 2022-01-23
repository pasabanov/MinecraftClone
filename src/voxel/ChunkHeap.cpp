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



bool ChunkHeap::voxelExists0(int chX, int chY, int chZ, int x, int y, int z) const {
    return chunkExists(chX, chY, chZ) && Chunk::voxelExists(x, y, z);
}

bool ChunkHeap::voxelNotNull0(int chX, int chY, int chZ, int x, int y, int z) const {
    return voxelExists0(chX, chY, chZ, x, y, z) && getChunk(chX, chY, chZ).getVoxel(x, y, z).getId() != 0;
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
                            int id = y <= ((sin(x*0.6)+cos(z*0.4)) * 0.5 + 0.5) * 10;
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

uint ChunkHeap::getVolume() const {
    return mChunks.size();
}



Chunk& ChunkHeap::getChunk(int x, int y, int z) {
    return mChunks[(y * mLength + z) * mWidth + x];
}

Chunk& ChunkHeap::getChunk(const glm::vec3& pos) {
    return getChunk(pos.x, pos.y, pos.z);
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
    return voxelExists0(chX, chY, chZ, x, y, z);
}

bool ChunkHeap::voxelNotNull(int chX, int chY, int chZ, int x, int y, int z) const {
    normalizeCoords(chX, chY, chZ, x, y, z);
    return voxelNotNull0(chX, chY, chZ, x, y, z);
}



const Voxel& ChunkHeap::getVoxelGlobal(int x, int y, int z) const {
    int chX = 0, chY = 0, chZ = 0;
    normalizeCoords(chX, chY, chZ, x, y, z);
    return getChunk(chX, chY, chZ).getVoxel(x, y, z);
}

void ChunkHeap::setVoxelGlobal(int x, int y, int z, const Voxel& newVoxel) {

    int chX = 0, chY = 0, chZ = 0;
    normalizeCoords(chX, chY, chZ, x, y, z);

    if (!voxelExists0(chX, chY, chZ, x, y, z))
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

    float stepx = (dx > 0.0f) ? 1.0f : -1.0f;
    float stepy = (dy > 0.0f) ? 1.0f : -1.0f;
    float stepz = (dz > 0.0f) ? 1.0f : -1.0f;

    float txDelta = (dx == 0.0f) ? infinity : std::abs(1.0f / dx);
    float tyDelta = (dy == 0.0f) ? infinity : std::abs(1.0f / dy);
    float tzDelta = (dz == 0.0f) ? infinity : std::abs(1.0f / dz);

    float xdist = (stepx > 0) ? (ix + 1 - px) : (px - ix);
    float ydist = (stepy > 0) ? (iy + 1 - py) : (py - iy);
    float zdist = (stepz > 0) ? (iz + 1 - pz) : (pz - iz);

    float txMax = (txDelta < infinity) ? txDelta * xdist : infinity;
    float tyMax = (tyDelta < infinity) ? tyDelta * ydist : infinity;
    float tzMax = (tzDelta < infinity) ? tzDelta * zdist : infinity;

    float t = 0.0f;

    int steppedIndex = -1;

    while (t <= maxDist) {

        int vX = ix, vY = iy, vZ = iz;
        int cX = 0, cY = 0, cZ = 0;
        normalizeCoords(cX, cY, cZ, vX, vY, vZ);

        Voxel* voxel = voxelExists0(cX, cY, cZ, vX, vY, vZ)
                ? &getChunk(cX, cY, cZ).getVoxel(vX, vY, vZ)
                : nullptr;

        if (voxel != nullptr && voxel->getId() != 0) {
            end.x = px + t * dx;
            end.y = py + t * dy;
            end.z = pz + t * dz;

            iend.x = ix;
            iend.y = iy;
            iend.z = iz;

            norm.x = norm.y = norm.z = 0.0f;
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
    norm.x = norm.y = norm.z = 0.0f;

    return nullptr;
}



int ChunkHeap::coordsToIndex(int x, int y, int z) const {
    return (y * mLength + z) * mWidth + x;
}