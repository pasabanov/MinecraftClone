#ifndef MINECRAFT_MESH_H
#define MINECRAFT_MESH_H

#include "../headers/includes.h"

class Mesh {

    uint mVAO, mVBO;
    uint mVerticesCount;

    void glDelete();

public:

    Mesh();
    Mesh(const float* buffer, uint verticesCount, const int* attrs);
    Mesh(Mesh&& other);

    ~Mesh();

    Mesh& operator=(Mesh&& other);

    void create(const float* buffer, uint verticesCount, const int* attrs);

    void draw(uint primitive = GL_TRIANGLES) const;
};

#endif //MINECRAFT_MESH_H