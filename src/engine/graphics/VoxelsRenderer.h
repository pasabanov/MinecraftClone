#ifndef MINECRAFT_VOXELSRENDERER_H
#define MINECRAFT_VOXELSRENDERER_H

#include "../../headers/includes.h"

#include "MeshHeap.h"
#include "../voxel/ChunkHeap.h"

class VoxelsRenderer {

    inline static const std::vector<int> VERTEX_ATTRS = {
            3, // x, y, z
            2, // texture coords
            1, // light
            0, // null-terminator
    };
    inline static const int VERTEX_SIZE = std::accumulate(VERTEX_ATTRS.begin(), VERTEX_ATTRS.end(), 0);

    bool mAmbientOcclusion = true;

    std::vector<float> mBuffer;

    void writeVertex(float x, float y, float z, float u, float v, float l);

public:

    VoxelsRenderer(uint startCapacity = 1024, bool ambientOcclusion = true);

    bool getAmbientOcclusion() const;
    void setAmbientOcclusion(bool ambientOcclusion);

    Mesh render(const ChunkHeap& chunks, int chX, int chY, int chZ);

    MeshHeap render(ChunkHeap& chunks);

    void render(ChunkHeap& chunks, MeshHeap& meshes);
};

#endif //MINECRAFT_VOXELSRENDERER_H