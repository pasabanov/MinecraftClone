#include "Mesh.h"



void Mesh::glDelete() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
}



Mesh::Mesh() {}

Mesh::Mesh(const float* buffer, uint verticesCount, const int* attrs) {
    create(buffer, verticesCount, attrs);
}

Mesh::Mesh(Mesh&& other)
: mVAO(other.mVAO), mVBO(other.mVBO), mVerticesCount(other.mVerticesCount) {
    other.mVAO = other.mVBO = other.mVerticesCount = GL_NONE;
}



Mesh::~Mesh() {
    glDelete();
}



Mesh& Mesh::operator=(Mesh&& other) {

    glDelete();

    mVAO = other.mVAO;
    mVBO = other.mVBO;
    mVerticesCount = other.mVerticesCount;

    other.mVAO = other.mVBO = other.mVerticesCount = GL_NONE;

    return *this;
}



void Mesh::draw(uint primitive) const {
    glBindVertexArray(mVAO);
    glDrawArrays(primitive, 0, mVerticesCount);
    glBindVertexArray(GL_NONE);
}



void Mesh::create(const float* buffer, uint verticesCount, const int* attrs) {

    glDelete();

    mVerticesCount = verticesCount;

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

    glBindVertexArray(GL_NONE);
}