#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "../headers/includes.h"

#include "Voxel.h"

class Chunk {

    std::vector<Voxel> mVoxels;

public:

    inline static const uint WIDTH = 16;
    inline static const uint HEIGHT = 16;
    inline static const uint LENGTH = 16;
    inline static const uint VOLUME = WIDTH * HEIGHT * LENGTH;

    Chunk();

    Voxel& voxel(uint x, uint y, uint z);
    const Voxel& getVoxel(uint x, uint y, uint z) const;
    void setVoxel(uint x, uint y, uint z, const Voxel& voxel);

    bool isIn(uint x, uint y, uint z) const;
    bool isBlocked(uint x, uint y, uint z) const;
};

#endif //MINECRAFT_CHUNK_H