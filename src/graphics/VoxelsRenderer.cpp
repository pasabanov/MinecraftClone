#include "VoxelsRenderer.h"



void VoxelsRenderer::writeVertex(uint& index, float x, float y, float z, float u, float v, float l) {
    mBuffer[index++] = x;
    mBuffer[index++] = y;
    mBuffer[index++] = z;
    mBuffer[index++] = u;
    mBuffer[index++] = v;
    mBuffer[index++] = l;
}



VoxelsRenderer::VoxelsRenderer(uint capacity) : mBuffer(capacity) {}



Mesh VoxelsRenderer::render(const Chunk& chunk) {
    uint index = 0;
    for (uint y = 0; y < Chunk::HEIGHT; ++y) {
        for (uint z = 0; z < Chunk::LENGTH; ++z) {
            for (uint x = 0; x < Chunk::WIDTH; ++x) {
                Voxel voxel = chunk.getVoxel(x, y, z);
                const int id = voxel.getId();
                if (!voxel.getId())
                    continue;

                float light;
                float uvsize = 1.0/16.0;
                float u = id % 16 * uvsize;
                float v = 1 - ((1 + id / 16) * uvsize);

                if (!chunk.isBlocked(x, y+1, z)) {
                    light = 1;
                    writeVertex(index, x - 0.5, y + 0.5, z - 0.5, u+uvsize, v, light);
                    writeVertex(index, x - 0.5, y + 0.5, z + 0.5, u+uvsize, v+uvsize, light);
                    writeVertex(index, x + 0.5, y + 0.5, z + 0.5, u, v+uvsize, light);

                    writeVertex(index, x - 0.5, y + 0.5, z - 0.5, u+uvsize, v, light);
                    writeVertex(index, x + 0.5, y + 0.5, z + 0.5, u, v+uvsize, light);
                    writeVertex(index, x + 0.5, y + 0.5, z - 0.5, u, v, light);
                }
                if (!chunk.isBlocked(x, y-1, z)) {
                    light = 0.75;
                    writeVertex(index, x - 0.5, y - 0.5, z - 0.5, u, v, light);
                    writeVertex(index, x + 0.5, y - 0.5, z + 0.5, u+uvsize, v+uvsize, light);
                    writeVertex(index, x - 0.5, y - 0.5, z + 0.5, u, v+uvsize, light);

                    writeVertex(index, x - 0.5, y - 0.5, z - 0.5, u, v, light);
                    writeVertex(index, x + 0.5, y - 0.5, z - 0.5, u+uvsize, v, light);
                    writeVertex(index, x + 0.5, y - 0.5, z + 0.5, u+uvsize, v+uvsize, light);
                }

                if (!chunk.isBlocked(x+1, y, z)) {
                    light = 0.95;
                    writeVertex(index, x + 0.5, y - 0.5, z - 0.5, u+uvsize, v, light);
                    writeVertex(index, x + 0.5, y + 0.5, z - 0.5, u+uvsize, v+uvsize, light);
                    writeVertex(index, x + 0.5, y + 0.5, z + 0.5, u, v+uvsize, light);

                    writeVertex(index, x + 0.5, y - 0.5, z - 0.5, u+uvsize, v, light);
                    writeVertex(index, x + 0.5, y + 0.5, z + 0.5, u, v+uvsize, light);
                    writeVertex(index, x + 0.5, y - 0.5, z + 0.5, u, v, light);
                }
                if (!chunk.isBlocked(x-1, y, z)) {
                    light = 0.85;
                    writeVertex(index, x - 0.5, y - 0.5, z - 0.5, u, v, light);
                    writeVertex(index, x - 0.5, y + 0.5, z + 0.5, u+uvsize, v+uvsize, light);
                    writeVertex(index, x - 0.5, y + 0.5, z - 0.5, u, v+uvsize, light);

                    writeVertex(index, x - 0.5, y - 0.5, z - 0.5, u, v, light);
                    writeVertex(index, x - 0.5, y - 0.5, z + 0.5, u+uvsize, v, light);
                    writeVertex(index, x - 0.5, y + 0.5, z + 0.5, u+uvsize, v+uvsize, light);
                }

                if (!chunk.isBlocked(x, y, z+1)) {
                    light = 0.9;
                    writeVertex(index, x - 0.5, y - 0.5, z + 0.5, u, v, light);
                    writeVertex(index, x + 0.5, y + 0.5, z + 0.5, u+uvsize, v+uvsize, light);
                    writeVertex(index, x - 0.5, y + 0.5, z + 0.5, u, v+uvsize, light);

                    writeVertex(index, x - 0.5, y - 0.5, z + 0.5, u, v, light);
                    writeVertex(index, x + 0.5, y - 0.5, z + 0.5, u+uvsize, v, light);
                    writeVertex(index, x + 0.5, y + 0.5, z + 0.5, u+uvsize, v+uvsize, light);
                }
                if (!chunk.isBlocked(x, y, z-1)) {
                    light = 0.8;
                    writeVertex(index, x - 0.5, y - 0.5, z - 0.5, u+uvsize, v, light);
                    writeVertex(index, x - 0.5, y + 0.5, z - 0.5, u+uvsize, v+uvsize, light);
                    writeVertex(index, x + 0.5, y + 0.5, z - 0.5, u, v+uvsize, light);

                    writeVertex(index, x - 0.5, y - 0.5, z - 0.5, u+uvsize, v, light);
                    writeVertex(index, x + 0.5, y + 0.5, z - 0.5, u, v+uvsize, light);
                    writeVertex(index, x + 0.5, y - 0.5, z - 0.5, u, v, light);
                }
            }
        }
    }
    return Mesh(mBuffer.data(), index / VERTEX_SIZE, CHUNK_ATTRS.data());
}