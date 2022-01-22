#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "../headers/includes.h"

#include "Voxel.h"

class Chunk {
public:

    std::vector<Voxel> mVoxels;

    inline static const uint WIDTH = 32;
    inline static const uint HEIGHT = 32;
    inline static const uint LENGTH = 32;
    inline static const uint VOLUME = WIDTH * HEIGHT * LENGTH;

    using VoxelGenerator = std::function<Voxel(uint,uint,uint)>;

    static bool voxelExists(int x, int y, int z);

    Chunk(const VoxelGenerator& generator = nullptr);

    void generateVoxels(const VoxelGenerator& generator);

    Voxel& voxel(uint x, uint y, uint z);
    Voxel& voxel(const glm::vec3& pos);
    const Voxel& getVoxel(uint x, uint y, uint z) const;
    const Voxel& getVoxel(const glm::vec3& pos);
    void setVoxel(uint x, uint y, uint z, const Voxel& voxel);
    void setVoxel(const glm::vec3& pos, const Voxel& voxel);
};

#endif //MINECRAFT_CHUNK_H