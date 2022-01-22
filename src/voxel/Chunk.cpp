#include "Chunk.h"



Chunk::Chunk() : mVoxels(VOLUME) {
    for (uint y = 0; y < HEIGHT; ++y) {
        for (uint z = 0; z < LENGTH; ++z) {
            for (uint x = 0; x < WIDTH; ++x) {
                int id = y <= (sin(x*0.6) * 0.5 + 0.5) * 10;
                if (y <= 2 && id != 0)
                    id = 2;
                mVoxels[(y * LENGTH + z) * WIDTH + x] = id;
            }
        }
    }
}



Voxel& Chunk::voxel(uint x, uint y, uint z) {
    return mVoxels[(y * LENGTH + z) * WIDTH + x];
}



const Voxel& Chunk::getVoxel(uint x, uint y, uint z) const {
    return mVoxels[(y * LENGTH + z) * WIDTH + x];
}



void Chunk::setVoxel(uint x, uint y, uint z, const Voxel& voxel) {
    mVoxels[(y * LENGTH + z) * WIDTH + x] = voxel;
}



bool Chunk::isIn(uint x, uint y, uint z) const {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && z >= 0 && z < LENGTH;
}



bool Chunk::isBlocked(uint x, uint y, uint z) const {
//    return !isIn(x, y, z) || getVoxel(x, y, z).getId() == 0;
    return isIn(x, y, z) && getVoxel(x, y, z).getId();
}