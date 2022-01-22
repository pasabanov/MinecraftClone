#ifndef MINECRAFT_VOXELSRENDERER_H
#define MINECRAFT_VOXELSRENDERER_H

#include "../headers/includes.h"

#include "MeshHeap.h"
#include "../voxel/ChunkHeap.h"

class VoxelsRenderer {

    inline static const std::vector<int> CHUNK_ATTRS = {
            3, // x, y, z
            2, // texture coords
            1, // light
            0, // null-terminator
    };
    inline static const int VERTEX_SIZE = std::accumulate(CHUNK_ATTRS.begin(), CHUNK_ATTRS.end(), 0);

    std::vector<float> mBuffer;

    void writeVertex(float x, float y, float z, float u, float v, float l);

public:

    VoxelsRenderer(uint startCapacity = 1024);

    MeshHeap render(const ChunkHeap& chunks);
};

#endif //MINECRAFT_VOXELSRENDERER_H