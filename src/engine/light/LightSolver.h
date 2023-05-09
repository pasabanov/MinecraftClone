#ifndef MINECRAFT_LIGHTSOLVER_H
#define MINECRAFT_LIGHTSOLVER_H

#include "../../headers/includes.h"

#include "../voxel/ChunkHeap.h"

class LightEntry {
public:
    int x, y, z;
    uchar light;
};

class LightSolver {

    std::queue<LightEntry> mAddQueue, mRemQueue;
    ChunkHeap* mChunks;
    int mChannel;

public:

    LightSolver(ChunkHeap* chunks, int channel);

    void add(int x, int y, int z);

    void add(int x, int y, int z, int emission);

    void remove(int x, int y, int z);

    void solve();
};

#endif //MINECRAFT_LIGHTSOLVER_H