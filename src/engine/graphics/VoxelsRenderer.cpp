#include "VoxelsRenderer.h"



void VoxelsRenderer::writeVertex(float x, float y, float z, float u, float v, float l) {
    mBuffer.push_back(x);
    mBuffer.push_back(y);
    mBuffer.push_back(z);
    mBuffer.push_back(u);
    mBuffer.push_back(v);
    mBuffer.push_back(l);
}



VoxelsRenderer::VoxelsRenderer(uint startCapacity, bool ambientOcclusion)
: mBuffer(startCapacity), mAmbientOcclusion(ambientOcclusion) {}



bool VoxelsRenderer::getAmbientOcclusion() const {
    return mAmbientOcclusion;
}

void VoxelsRenderer::setAmbientOcclusion(bool ambientOcclusion) {
    mAmbientOcclusion = ambientOcclusion;
}



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

                // AO values
                float a, b, c, d, e, f, g, h;
                a = b = c = d = e = f = g = h = 0.0;
                float aoFactor = 0.15;

                if (!chunks.voxelNotNull(chX, chY, chZ, x, y + 1, z)) {
                    light = 1;

                    if (mAmbientOcclusion) {
                        a = chunks.voxelNotNull(chX, chY, chZ, x+1,y+1,z)*aoFactor;
                        b = chunks.voxelNotNull(chX, chY, chZ, x,y+1,z+1)*aoFactor;
                        c = chunks.voxelNotNull(chX, chY, chZ, x-1,y+1,z)*aoFactor;
                        d = chunks.voxelNotNull(chX, chY, chZ, x,y+1,z-1)*aoFactor;

                        e = chunks.voxelNotNull(chX, chY, chZ, x-1,y+1,z-1)*aoFactor;
                        f = chunks.voxelNotNull(chX, chY, chZ, x-1,y+1,z+1)*aoFactor;
                        g = chunks.voxelNotNull(chX, chY, chZ, x+1,y+1,z+1)*aoFactor;
                        h = chunks.voxelNotNull(chX, chY, chZ, x+1,y+1,z-1)*aoFactor;
                    }

                    writeVertex(x, y + 1, z, u+uvsize, v, light*(1-c-d-e));
                    writeVertex(x, y + 1, z + 1, u+uvsize, v+uvsize, light*(1-c-b-f));
                    writeVertex(x + 1, y + 1, z + 1, u, v+uvsize, light*(1-a-b-g));

                    writeVertex(x, y + 1, z, u+uvsize, v, light*(1-c-d-e));
                    writeVertex(x + 1, y + 1, z + 1, u, v+uvsize, light*(1-a-b-g));
                    writeVertex(x + 1, y + 1, z, u, v, light*(1-a-d-h));
                }
                if (!chunks.voxelNotNull(chX, chY, chZ, x, y - 1, z)) {
                    light = 0.75;

                    if (mAmbientOcclusion) {
                        a = chunks.voxelNotNull(chX, chY, chZ, x+1,y-1,z)*aoFactor;
                        b = chunks.voxelNotNull(chX, chY, chZ, x,y-1,z+1)*aoFactor;
                        c = chunks.voxelNotNull(chX, chY, chZ, x-1,y-1,z)*aoFactor;
                        d = chunks.voxelNotNull(chX, chY, chZ, x,y-1,z-1)*aoFactor;

                        e = chunks.voxelNotNull(chX, chY, chZ, x-1,y-1,z-1)*aoFactor;
                        f = chunks.voxelNotNull(chX, chY, chZ, x-1,y-1,z+1)*aoFactor;
                        g = chunks.voxelNotNull(chX, chY, chZ, x+1,y-1,z+1)*aoFactor;
                        h = chunks.voxelNotNull(chX, chY, chZ, x+1,y-1,z-1)*aoFactor;
                    }

                    writeVertex(x, y, z, u, v, light*(1-c-d-e));
                    writeVertex(x + 1, y, z + 1, u+uvsize, v+uvsize, light*(1-a-b-g));
                    writeVertex(x, y, z + 1, u, v+uvsize, light*(1-c-b-f));

                    writeVertex(x, y, z, u, v, light*(1-c-d-e));
                    writeVertex(x + 1, y, z, u+uvsize, v, light*(1-a-d-h));
                    writeVertex(x + 1, y, z + 1, u+uvsize, v+uvsize, light*(1-a-b-g));
                }

                if (!chunks.voxelNotNull(chX, chY, chZ, x + 1, y, z)) {
                    light = 0.95;

                    if (mAmbientOcclusion) {
                        a = chunks.voxelNotNull(chX, chY, chZ, x+1,y+1,z)*aoFactor;
                        b = chunks.voxelNotNull(chX, chY, chZ, x+1,y,  z+1)*aoFactor;
                        c = chunks.voxelNotNull(chX, chY, chZ, x+1,y-1,z)*aoFactor;
                        d = chunks.voxelNotNull(chX, chY, chZ, x+1,y,  z-1)*aoFactor;

                        e = chunks.voxelNotNull(chX, chY, chZ, x+1,y-1,z-1)*aoFactor;
                        f = chunks.voxelNotNull(chX, chY, chZ, x+1,y-1,z+1)*aoFactor;
                        g = chunks.voxelNotNull(chX, chY, chZ, x+1,y+1,z+1)*aoFactor;
                        h = chunks.voxelNotNull(chX, chY, chZ, x+1,y+1,z-1)*aoFactor;
                    }

                    writeVertex(x + 1, y, z, u+uvsize, v, light*(1-c-d-e));
                    writeVertex(x + 1, y + 1, z, u+uvsize, v+uvsize, light*(1-d-a-h));
                    writeVertex(x + 1, y + 1, z + 1, u, v+uvsize, light*(1-a-b-g));

                    writeVertex(x + 1, y, z, u+uvsize, v, light*(1-c-d-e));
                    writeVertex(x + 1, y + 1, z + 1, u, v+uvsize, light*(1-a-b-g));
                    writeVertex(x + 1, y, z + 1, u, v, light*(1-b-c-f));
                }
                if (!chunks.voxelNotNull(chX, chY, chZ, x - 1, y, z)) {
                    light = 0.85;

                    if (mAmbientOcclusion){
                        a = chunks.voxelNotNull(chX, chY, chZ, x-1,y+1,z)*aoFactor;
                        b = chunks.voxelNotNull(chX, chY, chZ, x-1,y,  z+1)*aoFactor;
                        c = chunks.voxelNotNull(chX, chY, chZ, x-1,y-1,z)*aoFactor;
                        d = chunks.voxelNotNull(chX, chY, chZ, x-1,y,  z-1)*aoFactor;

                        e = chunks.voxelNotNull(chX, chY, chZ, x-1,y-1,z-1)*aoFactor;
                        f = chunks.voxelNotNull(chX, chY, chZ, x-1,y-1,z+1)*aoFactor;
                        g = chunks.voxelNotNull(chX, chY, chZ, x-1,y+1,z+1)*aoFactor;
                        h = chunks.voxelNotNull(chX, chY, chZ, x-1,y+1,z-1)*aoFactor;
                    }

                    writeVertex(x, y, z, u, v, light*(1-c-d-e));
                    writeVertex(x, y + 1, z + 1, u+uvsize, v+uvsize, light*(1-a-b-g));
                    writeVertex(x, y + 1, z, u, v+uvsize, light*(1-d-a-h));

                    writeVertex(x, y, z, u, v, light*(1-c-d-e));
                    writeVertex(x, y, z + 1, u+uvsize, v, light*(1-b-c-f));
                    writeVertex(x, y + 1, z + 1, u+uvsize, v+uvsize, light*(1-a-b-g));
                }

                if (!chunks.voxelNotNull(chX, chY, chZ, x, y, z + 1)) {
                    light = 0.9;

                    if (mAmbientOcclusion){
                        a = chunks.voxelNotNull(chX, chY, chZ, x,  y+1,z+1)*aoFactor;
                        b = chunks.voxelNotNull(chX, chY, chZ, x+1,y,  z+1)*aoFactor;
                        c = chunks.voxelNotNull(chX, chY, chZ, x,  y-1,z+1)*aoFactor;
                        d = chunks.voxelNotNull(chX, chY, chZ, x-1,y,  z+1)*aoFactor;

                        e = chunks.voxelNotNull(chX, chY, chZ, x-1,y-1,z+1)*aoFactor;
                        f = chunks.voxelNotNull(chX, chY, chZ, x+1,y-1,z+1)*aoFactor;
                        g = chunks.voxelNotNull(chX, chY, chZ, x+1,y+1,z+1)*aoFactor;
                        h = chunks.voxelNotNull(chX, chY, chZ, x-1,y+1,z+1)*aoFactor;
                    }

                    writeVertex(x, y, z + 1, u, v, light*(1-c-d-e));
                    writeVertex(x + 1, y + 1, z + 1, u+uvsize, v+uvsize, light*(1-a-b-g));
                    writeVertex(x, y + 1, z + 1, u, v+uvsize, light*(1-a-d-h));

                    writeVertex(x, y, z + 1, u, v, light*(1-c-d-e));
                    writeVertex(x + 1, y, z + 1, u+uvsize, v, light*(1-b-c-f));
                    writeVertex(x + 1, y + 1, z + 1, u+uvsize, v+uvsize, light*(1-a-b-g));
                }
                if (!chunks.voxelNotNull(chX, chY, chZ, x, y, z - 1)) {
                    light = 0.8;

                    if (mAmbientOcclusion){
                        a = chunks.voxelNotNull(chX, chY, chZ, x,  y+1,z-1)*aoFactor;
                        b = chunks.voxelNotNull(chX, chY, chZ, x+1,y,  z-1)*aoFactor;
                        c = chunks.voxelNotNull(chX, chY, chZ, x,  y-1,z-1)*aoFactor;
                        d = chunks.voxelNotNull(chX, chY, chZ, x-1,y,  z-1)*aoFactor;

                        e = chunks.voxelNotNull(chX, chY, chZ, x-1,y-1,z-1)*aoFactor;
                        f = chunks.voxelNotNull(chX, chY, chZ, x+1,y-1,z-1)*aoFactor;
                        g = chunks.voxelNotNull(chX, chY, chZ, x+1,y+1,z-1)*aoFactor;
                        h = chunks.voxelNotNull(chX, chY, chZ, x-1,y+1,z-1)*aoFactor;
                    }

                    writeVertex(x, y, z, u+uvsize, v, light*(1-c-d-e));
                    writeVertex(x, y + 1, z, u+uvsize, v+uvsize, light*(1-a-d-h));
                    writeVertex(x + 1, y + 1, z, u, v+uvsize, light*(1-a-b-g));

                    writeVertex(x, y, z, u+uvsize, v, light*(1-c-d-e));
                    writeVertex(x + 1, y + 1, z, u, v+uvsize, light*(1-a-b-g));
                    writeVertex(x + 1, y, z, u, v, light*(1-b-c-f));
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