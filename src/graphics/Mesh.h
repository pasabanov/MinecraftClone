#ifndef MINECRAFT_MESH_H
#define MINECRAFT_MESH_H

#include "../headers/includes.h"

class Mesh {

    uint mVAO, mVBO;
    uint mVerticesCount;

public:

    Mesh(const float* buffer, uint verticesCount, const int* attrs);

    ~Mesh();

    void draw(uint primitive);
};

#endif //MINECRAFT_MESH_H