#include "VoxelsRenderer.h"



void VoxelsRenderer::writeVertex(float x, float y, float z, float u, float v, float l) {
    mBuffer.push_back(x);
    mBuffer.push_back(y);
    mBuffer.push_back(z);
    mBuffer.push_back(u);
    mBuffer.push_back(v);
    mBuffer.push_back(l);
}



VoxelsRenderer::VoxelsRenderer(uint startCapacity) : mBuffer(startCapacity) {}



Mesh VoxelsRenderer::render(const ChunkHeap& chunks, int chX, int chY, int chZ) {

    mBuffer.resize(0);

    const Chunk& chunk = chunks.getChunk(chX, chY, chZ);

    for (int y = 0; y < Chunk::HEIGHT; ++y) {
        for (int z = 0; z < Chunk::LENGTH; ++z) {
            for (int x = 0; x < Chunk::WIDTH; ++x) {

                Voxel voxel = chunk.getVoxel(x, y, z);

                const int id = voxel.getId();

                if (!voxel.getId())
                    continue;

                float light;
                float uvsize = 1.0/16.0;
                float u = id % 16 * uvsize;
                float v = 1 - ((1 + id / 16) * uvsize);

                if (!chunks.voxelNotNull(chX, chY, chZ, x, y + 1, z)) {
                    light = 1;
                    writeVertex(x, y + 1, z, u+uvsize, v, light);
                    writeVertex(x, y + 1, z + 1, u+uvsize, v+uvsize, light);
                    writeVertex(x + 1, y + 1, z + 1, u, v+uvsize, light);

                    writeVertex(x, y + 1, z, u+uvsize, v, light);
                    writeVertex(x + 1, y + 1, z + 1, u, v+uvsize, light);
                    writeVertex(x + 1, y + 1, z, u, v, light);
                }
                if (!chunks.voxelNotNull(chX, chY, chZ, x, y - 1, z)) {
                    light = 0.75;
                    writeVertex(x, y, z, u, v, light);
                    writeVertex(x + 1, y, z + 1, u+uvsize, v+uvsize, light);
                    writeVertex(x, y, z + 1, u, v+uvsize, light);

                    writeVertex(x, y, z, u, v, light);
                    writeVertex(x + 1, y, z, u+uvsize, v, light);
                    writeVertex(x + 1, y, z + 1, u+uvsize, v+uvsize, light);
                }

                if (!chunks.voxelNotNull(chX, chY, chZ, x + 1, y, z)) {
                    light = 0.95;
                    writeVertex(x + 1, y, z, u+uvsize, v, light);
                    writeVertex(x + 1, y + 1, z, u+uvsize, v+uvsize, light);
                    writeVertex(x + 1, y + 1, z + 1, u, v+uvsize, light);

                    writeVertex(x + 1, y, z, u+uvsize, v, light);
                    writeVertex(x + 1, y + 1, z + 1, u, v+uvsize, light);
                    writeVertex(x + 1, y, z + 1, u, v, light);
                }
                if (!chunks.voxelNotNull(chX, chY, chZ, x - 1, y, z)) {
                    light = 0.85;
                    writeVertex(x, y, z, u, v, light);
                    writeVertex(x, y + 1, z + 1, u+uvsize, v+uvsize, light);
                    writeVertex(x, y + 1, z, u, v+uvsize, light);

                    writeVertex(x, y, z, u, v, light);
                    writeVertex(x, y, z + 1, u+uvsize, v, light);
                    writeVertex(x, y + 1, z + 1, u+uvsize, v+uvsize, light);
                }

                if (!chunks.voxelNotNull(chX, chY, chZ, x, y, z + 1)) {
                    light = 0.9;
                    writeVertex(x, y, z + 1, u, v, light);
                    writeVertex(x + 1, y + 1, z + 1, u+uvsize, v+uvsize, light);
                    writeVertex(x, y + 1, z + 1, u, v+uvsize, light);

                    writeVertex(x, y, z + 1, u, v, light);
                    writeVertex(x + 1, y, z + 1, u+uvsize, v, light);
                    writeVertex(x + 1, y + 1, z + 1, u+uvsize, v+uvsize, light);
                }
                if (!chunks.voxelNotNull(chX, chY, chZ, x, y, z - 1)) {
                    light = 0.8;
                    writeVertex(x, y, z, u+uvsize, v, light);
                    writeVertex(x, y + 1, z, u+uvsize, v+uvsize, light);
                    writeVertex(x + 1, y + 1, z, u, v+uvsize, light);

                    writeVertex(x, y, z, u+uvsize, v, light);
                    writeVertex(x + 1, y + 1, z, u, v+uvsize, light);
                    writeVertex(x + 1, y, z, u, v, light);
                }
            }
        }
    }

    Mesh mesh (mBuffer.data(),
               mBuffer.size() / VERTEX_SIZE,
               VERTEX_ATTRS.data());

    return mesh;
}



MeshHeap VoxelsRenderer::render(ChunkHeap& chunks) {

    MeshHeap meshes (chunks.getVolume());

    render(chunks, meshes);

    return meshes;
}



void VoxelsRenderer::render(ChunkHeap& chunks, MeshHeap& meshes) {

    for (int chY = 0; chY < chunks.getHeight(); ++chY) {
        for (int chZ = 0; chZ < chunks.getLength(); ++chZ) {
            for (int chX = 0; chX < chunks.getWidth(); ++chX) {
                Chunk& chunk = chunks.getChunk(chX, chY, chZ);
                if (!chunk.isModified())
                    continue;
                chunk.setModified(false);
                meshes.set(
                        render(chunks, chX, chY, chZ),
                        { chX*Chunk::WIDTH, chY*Chunk::HEIGHT, chZ*Chunk::LENGTH },
                        chunks.coordsToIndex(chX, chY, chZ)
                );
            }
        }
    }
}