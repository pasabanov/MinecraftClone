#ifndef MINECRAFT_VOXELSRENDERER_H
#define MINECRAFT_VOXELSRENDERER_H

#include "../headers/includes.h"

#include "Mesh.h"
#include "../voxel/Chunk.h"

class VoxelsRenderer {

    inline static const std::vector<int> CHUNK_ATTRS = {
            3, // x, y, z
            2, // texture coords
            1, // light
            0, // null-terminator
    };
    inline static const int VERTEX_SIZE = CHUNK_ATTRS.size() - 1;

    std::vector<float> mBuffer;

    void writeVertex(uint& index, float x, float y, float z, float u, float v, float l);

public:

    VoxelsRenderer(uint capacity);

    Mesh render(const Chunk& chunk);
};

#endif //MINECRAFT_VOXELSRENDERER_H