#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "../../headers/includes.h"

#include "Voxel.h"
#include "../light/LightMap.h"

class Chunk {

    int mX, mY, mZ;
    std::vector<Voxel> mVoxels;
    LightMap mLightMap {};
    bool mModified = true;

public:

    inline static const int WIDTH = 32;
    inline static const int HEIGHT = 32;
    inline static const int LENGTH = 32;
    inline static const int VOLUME = WIDTH * HEIGHT * LENGTH;

    using VoxelGenerator = std::function<Voxel(uint,uint,uint)>;

    static bool voxelExists(int x, int y, int z);

    Chunk(int x = 0, int y = 0, int z = 0, const VoxelGenerator& generator = nullptr);

    void generateVoxels(const VoxelGenerator& generator);

    int getX() const;
    int getY() const;
    int getZ() const;
    void setX(int x);
    void setY(int y);
    void setZ(int z);

    Voxel& getVoxel(uint x, uint y, uint z);
    const Voxel& getVoxel(uint x, uint y, uint z) const;
    void setVoxel(uint x, uint y, uint z, const Voxel& voxel);

    ubyte getLight(int x, int y, int z, int channel) const;
    void setLight(int x, int y, int z, int channel, int value);

    bool isModified() const;
    void setModified(bool modified);

    Voxel& getVoxel(int index);
    const Voxel& getVoxel(int index) const;
    void setVoxel(int index, const Voxel& voxel);
};

#endif //MINECRAFT_CHUNK_H