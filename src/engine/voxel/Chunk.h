#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "../../headers/includes.h"

#include "Voxel.h"

class Chunk {

    std::vector<Voxel> mVoxels;
    bool mModified = true;

public:

    inline static const int WIDTH = 32;
    inline static const int HEIGHT = 32;
    inline static const int LENGTH = 32;
    inline static const int VOLUME = WIDTH * HEIGHT * LENGTH;

    using VoxelGenerator = std::function<Voxel(uint,uint,uint)>;

    static bool voxelExists(int x, int y, int z);

    Chunk(const VoxelGenerator& generator = nullptr);

    void generateVoxels(const VoxelGenerator& generator);

    Voxel& getVoxel(uint x, uint y, uint z);
    Voxel& getVoxel(const glm::vec3& pos);
    const Voxel& getVoxel(uint x, uint y, uint z) const;
    const Voxel& getVoxel(const glm::vec3& pos) const;
    void setVoxel(uint x, uint y, uint z, const Voxel& voxel);
    void setVoxel(const glm::vec3& pos, const Voxel& voxel);

    bool isModified() const;
    void setModified(bool modified);
};

#endif //MINECRAFT_CHUNK_H