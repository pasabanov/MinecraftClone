#include <engine/graphics/VoxelsRenderer.h>

void VoxelsRenderer::writeVertex(float x, float y, float z, float u, float v, float r, float g, float b, float s) {
    mBuffer.push_back(x);
    mBuffer.push_back(y);
    mBuffer.push_back(z);

    mBuffer.push_back(u);
    mBuffer.push_back(v);

    mBuffer.push_back(r);
    mBuffer.push_back(g);
    mBuffer.push_back(b);
    mBuffer.push_back(s);
}

VoxelsRenderer::VoxelsRenderer(uint startCapacity) : mBuffer(startCapacity) {}

Mesh VoxelsRenderer::render(const ChunkHeap& chunks, int chX, int chY, int chZ) {

    mBuffer.resize(0);

    const Chunk& chunk = chunks.getChunk(chX, chY, chZ);

    for (int y = 0; y < Chunk::HEIGHT; ++y) {
        for (int z = 0; z < Chunk::LENGTH; ++z) {
            for (int x = 0; x < Chunk::WIDTH; ++x) {

                const Voxel& voxel = chunk.getVoxel(x, y, z);

                const int id = voxel.getId();

                if (!voxel.getId())
                    continue;

                float light = 1;
                float uvsize = 1.0/16.0;
                float u1 = id % 16 * uvsize;
                float v1 = 1 - ((1 + id / 16) * uvsize);
                float u2 = u1 + uvsize;
                float v2 = v1 + uvsize;

//                // AO values
//                float a, b, c, d, e, f, g, h;
//                a = b = c = d = e = f = g = h = 0.0;
//                float aoFactor = 0.15;

                float l = 1;

                if (!chunks.voxelNotNull(chX, chY, chZ, x, y+1, z)) {

                    float lr = chunks.getLight(chX, chY, chZ, x, y+1, z, 0) / 15.0;
                    float lg = chunks.getLight(chX, chY, chZ, x, y+1, z, 1) / 15.0;
                    float lb = chunks.getLight(chX, chY, chZ, x, y+1, z, 2) / 15.0;
                    float ls = chunks.getLight(chX, chY, chZ, x, y+1, z, 3) / 15.0;

                    float lr0 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 0) + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 0)) / 5.0 / 15.0;
                    float lr1 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 0) + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 0)) / 5.0 / 15.0;
                    float lr2 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 0) + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 0)) / 5.0 / 15.0;
                    float lr3 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 0) + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 0)) / 5.0 / 15.0;

                    float lg0 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 1) + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 1)) / 5.0 / 15.0;
                    float lg1 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 1) + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 1)) / 5.0 / 15.0;
                    float lg2 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 1) + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 1)) / 5.0 / 15.0;
                    float lg3 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 1) + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 1)) / 5.0 / 15.0;

                    float lb0 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 2) + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 2)) / 5.0 / 15.0;
                    float lb1 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 2) + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 2)) / 5.0 / 15.0;
                    float lb2 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 2) + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 2)) / 5.0 / 15.0;
                    float lb3 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 2) + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 2)) / 5.0 / 15.0;

                    float ls0 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 3) + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 3)) / 5.0 / 15.0;
                    float ls1 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 3) + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 3)) / 5.0 / 15.0;
                    float ls2 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 3) + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 3)) / 5.0 / 15.0;
                    float ls3 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 3) + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 3)) / 5.0 / 15.0;

                    writeVertex(x, y + 1, z, u2, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x, y + 1, z + 1, u2, v2, lr1, lg1, lb1, ls1);
                    writeVertex(x + 1, y + 1, z + 1, u1, v2, lr2, lg2, lb2, ls2);

                    writeVertex(x, y + 1, z, u2, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x + 1, y + 1, z + 1, u1, v2, lr2, lg2, lb2, ls2);
                    writeVertex(x + 1, y + 1, z, u1, v1, lr3, lg3, lb3, ls3);
                }

                if (!chunks.voxelNotNull(chX, chY, chZ, x, y-1, z)) {

                    float lr = chunks.getLight(chX, chY, chZ, x, y-1, z, 0) / 15.0;
                    float lg = chunks.getLight(chX, chY, chZ, x, y-1, z, 1) / 15.0;
                    float lb = chunks.getLight(chX, chY, chZ, x, y-1, z, 2) / 15.0;
                    float ls = chunks.getLight(chX, chY, chZ, x, y-1, z, 3) / 15.0;

                    float lr0 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 0) + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 0)) / 5.0 / 15.0;
                    float lr1 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 0) + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 0)) / 5.0 / 15.0;
                    float lr2 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 0) + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 0)) / 5.0 / 15.0;
                    float lr3 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 0) + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 0)) / 5.0 / 15.0;

                    float lg0 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 1) + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 1)) / 5.0 / 15.0;
                    float lg1 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 1) + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 1)) / 5.0 / 15.0;
                    float lg2 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 1) + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 1)) / 5.0 / 15.0;
                    float lg3 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 1) + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 1)) / 5.0 / 15.0;

                    float lb0 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 2) + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 2)) / 5.0 / 15.0;
                    float lb1 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 2) + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 2)) / 5.0 / 15.0;
                    float lb2 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 2) + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 2)) / 5.0 / 15.0;
                    float lb3 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 2) + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 2)) / 5.0 / 15.0;

                    float ls0 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 3) + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 3)) / 5.0 / 15.0;
                    float ls1 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 3) + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 3)) / 5.0 / 15.0;
                    float ls2 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 3) + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 3)) / 5.0 / 15.0;
                    float ls3 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 3) + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 3)) / 5.0 / 15.0;

                    writeVertex(x, y, z, u1, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x + 1, y, z + 1, u2, v2, lr1, lg1, lb1, ls1);
                    writeVertex(x, y, z + 1, u1, v2, lr2, lg2, lb2, ls2);

                    writeVertex(x, y, z, u1, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x + 1, y, z, u2, v1, lr3, lg3, lb3, ls3);
                    writeVertex(x + 1, y, z + 1, u2, v2, lr1, lg1, lb1, ls1);
                }

                if (!chunks.voxelNotNull(chX, chY, chZ, x+1, y, z)) {

                    float lr = chunks.getLight(chX, chY, chZ, x+1, y, z, 0) / 15.0;
                    float lg = chunks.getLight(chX, chY, chZ, x+1, y, z, 1) / 15.0;
                    float lb = chunks.getLight(chX, chY, chZ, x+1, y, z, 2) / 15.0;
                    float ls = chunks.getLight(chX, chY, chZ, x+1, y, z, 3) / 15.0;

                    float lr0 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 0) + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 0)) / 5.0 / 15.0;
                    float lr1 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 0) + chunks.getLight(chX, chY, chZ, x+1, y+1, z, 0)) / 5.0 / 15.0;
                    float lr2 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 0) + chunks.getLight(chX, chY, chZ, x+1, y+1, z, 0)) / 5.0 / 15.0;
                    float lr3 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 0) + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 0)) / 5.0 / 15.0;

                    float lg0 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 1) + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 1)) / 5.0 / 15.0;
                    float lg1 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 1) + chunks.getLight(chX, chY, chZ, x+1, y+1, z, 1)) / 5.0 / 15.0;
                    float lg2 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 1) + chunks.getLight(chX, chY, chZ, x+1, y+1, z, 1)) / 5.0 / 15.0;
                    float lg3 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 1) + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 1)) / 5.0 / 15.0;

                    float lb0 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 2) + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 2)) / 5.0 / 15.0;
                    float lb1 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 2) + chunks.getLight(chX, chY, chZ, x+1, y+1, z, 2)) / 5.0 / 15.0;
                    float lb2 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 2) + chunks.getLight(chX, chY, chZ, x+1, y+1, z, 2)) / 5.0 / 15.0;
                    float lb3 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 2) + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 2)) / 5.0 / 15.0;

                    float ls0 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 3) + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 3)) / 5.0 / 15.0;
                    float ls1 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 3) + chunks.getLight(chX, chY, chZ, x+1, y+1, z, 3)) / 5.0 / 15.0;
                    float ls2 = (chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 3) + chunks.getLight(chX, chY, chZ, x+1, y+1, z, 3)) / 5.0 / 15.0;
                    float ls3 = (chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 3) + chunks.getLight(chX, chY, chZ, x+1, y-1, z, 3)) / 5.0 / 15.0;

                    writeVertex(x + 1, y, z, u2, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x + 1, y + 1, z, u2, v2, lr1, lg1, lb1, ls1);
                    writeVertex(x + 1, y + 1, z + 1, u1, v2, lr2, lg2, lb2, ls2);

                    writeVertex(x + 1, y, z, u2, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x + 1, y + 1, z + 1, u1, v2, lr2, lg2, lb2, ls2);
                    writeVertex(x + 1, y, z + 1, u1, v1, lr3, lg3, lb3, ls3);
                }

                if (!chunks.voxelNotNull(chX, chY, chZ, x-1, y, z)) {

                    float lr = chunks.getLight(chX, chY, chZ, x-1, y, z, 0) / 15.0;
                    float lg = chunks.getLight(chX, chY, chZ, x-1, y, z, 1) / 15.0;
                    float lb = chunks.getLight(chX, chY, chZ, x-1, y, z, 2) / 15.0;
                    float ls = chunks.getLight(chX, chY, chZ, x-1, y, z, 3) / 15.0;

                    float lr0 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 0) + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 0)) / 5.0 / 15.0;
                    float lr1 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 0) + chunks.getLight(chX, chY, chZ, x-1, y+1, z, 0)) / 5.0 / 15.0;
                    float lr2 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 0) + chunks.getLight(chX, chY, chZ, x-1, y+1, z, 0)) / 5.0 / 15.0;
                    float lr3 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 0) + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 0)) / 5.0 / 15.0;

                    float lg0 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 1) + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 1)) / 5.0 / 15.0;
                    float lg1 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 1) + chunks.getLight(chX, chY, chZ, x-1, y+1, z, 1)) / 5.0 / 15.0;
                    float lg2 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 1) + chunks.getLight(chX, chY, chZ, x-1, y+1, z, 1)) / 5.0 / 15.0;
                    float lg3 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 1) + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 1)) / 5.0 / 15.0;

                    float lb0 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 2) + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 2)) / 5.0 / 15.0;
                    float lb1 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 2) + chunks.getLight(chX, chY, chZ, x-1, y+1, z, 2)) / 5.0 / 15.0;
                    float lb2 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 2) + chunks.getLight(chX, chY, chZ, x-1, y+1, z, 2)) / 5.0 / 15.0;
                    float lb3 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 2) + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 2)) / 5.0 / 15.0;

                    float ls0 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 3) + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 3)) / 5.0 / 15.0;
                    float ls1 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 3) + chunks.getLight(chX, chY, chZ, x-1, y+1, z, 3)) / 5.0 / 15.0;
                    float ls2 = (chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 3) + chunks.getLight(chX, chY, chZ, x-1, y+1, z, 3)) / 5.0 / 15.0;
                    float ls3 = (chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 3) + chunks.getLight(chX, chY, chZ, x-1, y-1, z, 3)) / 5.0 / 15.0;

                    writeVertex(x, y, z, u1, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x, y + 1, z + 1, u2, v2, lr1, lg1, lb1, ls1);
                    writeVertex(x, y + 1, z, u1, v2, lr2, lg2, lb2, ls2);

                    writeVertex(x, y, z, u1, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x, y, z + 1, u2, v1, lr3, lg3, lb3, ls3);
                    writeVertex(x, y + 1, z + 1, u2, v2, lr1, lg1, lb1, ls1);
                }

                if (!chunks.voxelNotNull(chX, chY, chZ, x, y, z+1)) {

                    float lr = chunks.getLight(chX, chY, chZ, x, y, z+1, 0) / 15.0;
                    float lg = chunks.getLight(chX, chY, chZ, x, y, z+1, 1) / 15.0;
                    float lb = chunks.getLight(chX, chY, chZ, x, y, z+1, 2) / 15.0;
                    float ls = chunks.getLight(chX, chY, chZ, x, y, z+1, 3) / 15.0;

                    float lr0 = l*(chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 0) + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 0)) / 5.0 / 15.0;
                    float lr1 = l*(chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 0) + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 0)) / 5.0 / 15.0;
                    float lr2 = l*(chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 0) + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 0)) / 5.0 / 15.0;
                    float lr3 = l*(chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 0) + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 0)) / 5.0 / 15.0;

                    float lg0 = l*(chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 1) + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 1)) / 5.0 / 15.0;
                    float lg1 = l*(chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 1) + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 1)) / 5.0 / 15.0;
                    float lg2 = l*(chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 1) + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 1)) / 5.0 / 15.0;
                    float lg3 = l*(chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 1) + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 1)) / 5.0 / 15.0;

                    float lb0 = l*(chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 2) + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 2)) / 5.0 / 15.0;
                    float lb1 = l*(chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 2) + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 2)) / 5.0 / 15.0;
                    float lb2 = l*(chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 2) + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 2)) / 5.0 / 15.0;
                    float lb3 = l*(chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 2) + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 2)) / 5.0 / 15.0;

                    float ls0 = l*(chunks.getLight(chX, chY, chZ, x-1, y-1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 3) + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 3)) / 5.0 / 15.0;
                    float ls1 = l*(chunks.getLight(chX, chY, chZ, x+1, y+1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 3) + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 3)) / 5.0 / 15.0;
                    float ls2 = l*(chunks.getLight(chX, chY, chZ, x-1, y+1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x, y+1, z+1, 3) + chunks.getLight(chX, chY, chZ, x-1, y, z+1, 3)) / 5.0 / 15.0;
                    float ls3 = l*(chunks.getLight(chX, chY, chZ, x+1, y-1, z+1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x, y-1, z+1, 3) + chunks.getLight(chX, chY, chZ, x+1, y, z+1, 3)) / 5.0 / 15.0;

                    writeVertex(x, y, z + 1, u1, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x + 1, y + 1, z + 1, u2, v2, lr1, lg1, lb1, ls1);
                    writeVertex(x, y + 1, z + 1, u1, v2, lr2, lg2, lb2, ls2);

                    writeVertex(x, y, z + 1, u1, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x + 1, y, z + 1, u2, v1, lr3, lg3, lb3, ls3);
                    writeVertex(x + 1, y + 1, z + 1, u2, v2, lr1, lg1, lb1, ls1);
                }

                if (!chunks.voxelNotNull(chX, chY, chZ, x, y, z-1)) {

                    float lr = chunks.getLight(chX, chY, chZ, x, y, z-1, 0) / 15.0;
                    float lg = chunks.getLight(chX, chY, chZ, x, y, z-1, 1) / 15.0;
                    float lb = chunks.getLight(chX, chY, chZ, x, y, z-1, 2) / 15.0;
                    float ls = chunks.getLight(chX, chY, chZ, x, y, z-1, 3) / 15.0;

                    float lr0 = l*(chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 0) + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 0)) / 5.0 / 15.0;
                    float lr1 = l*(chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 0) + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 0)) / 5.0 / 15.0;
                    float lr2 = l*(chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 0) + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 0)) / 5.0 / 15.0;
                    float lr3 = l*(chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 0) + lr*30 + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 0) + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 0)) / 5.0 / 15.0;

                    float lg0 = l*(chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 1) + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 1)) / 5.0 / 15.0;
                    float lg1 = l*(chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 1) + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 1)) / 5.0 / 15.0;
                    float lg2 = l*(chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 1) + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 1)) / 5.0 / 15.0;
                    float lg3 = l*(chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 1) + lg*30 + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 1) + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 1)) / 5.0 / 15.0;

                    float lb0 = l*(chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 2) + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 2)) / 5.0 / 15.0;
                    float lb1 = l*(chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 2) + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 2)) / 5.0 / 15.0;
                    float lb2 = l*(chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 2) + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 2)) / 5.0 / 15.0;
                    float lb3 = l*(chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 2) + lb*30 + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 2) + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 2)) / 5.0 / 15.0;

                    float ls0 = l*(chunks.getLight(chX, chY, chZ, x-1, y-1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 3) + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 3)) / 5.0 / 15.0;
                    float ls1 = l*(chunks.getLight(chX, chY, chZ, x-1, y+1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 3) + chunks.getLight(chX, chY, chZ, x-1, y, z-1, 3)) / 5.0 / 15.0;
                    float ls2 = l*(chunks.getLight(chX, chY, chZ, x+1, y+1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x, y+1, z-1, 3) + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 3)) / 5.0 / 15.0;
                    float ls3 = l*(chunks.getLight(chX, chY, chZ, x+1, y-1, z-1, 3) + ls*30 + chunks.getLight(chX, chY, chZ, x, y-1, z-1, 3) + chunks.getLight(chX, chY, chZ, x+1, y, z-1, 3)) / 5.0 / 15.0;

                    writeVertex(x, y, z, u2, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x, y + 1, z, u2, v2, lr1, lg1, lb1, ls1);
                    writeVertex(x + 1, y + 1, z, u1, v2, lr2, lg2, lb2, ls2);

                    writeVertex(x, y, z, u2, v1, lr0, lg0, lb0, ls0);
                    writeVertex(x + 1, y + 1, z, u1, v2, lr2, lg2, lb2, ls2);
                    writeVertex(x + 1, y, z, u1, v1, lr3, lg3, lb3, ls3);
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