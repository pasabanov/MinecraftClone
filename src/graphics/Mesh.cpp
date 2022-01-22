#include "Mesh.h"



Mesh::Mesh(const float* buffer, uint verticesCount, const int* attrs) : mVerticesCount(verticesCount) {

    int vertex_size = 0;
    for (int i = 0; attrs[i]; ++i)
        vertex_size += attrs[i];

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * verticesCount, buffer, GL_STATIC_DRAW);

    // attributes
    for (int i = 0, offset = 0; attrs[i]; ++i) {
        int size = attrs[i];
        glVertexAttribPointer(i, size, GL_FLOAT, false, vertex_size * sizeof(float),
                              (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += size;
    }

    glBindVertexArray(-1);
}


Mesh::~Mesh() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
}



void Mesh::draw(uint primitive) {
    glBindVertexArray(mVAO);
    glDrawArrays(primitive, 0, mVerticesCount);
    glBindVertexArray(-1);
}