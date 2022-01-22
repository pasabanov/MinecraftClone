#ifndef MINECRAFT_MESHHEAP_H
#define MINECRAFT_MESHHEAP_H

#include "../headers/includes.h"

#include "Mesh.h"

class MeshHeap {

    std::vector<Mesh> mMeshes;
    std::vector<glm::mat4> mModels;

public:

    MeshHeap();

    int size() const;

    void add(Mesh&& mesh, const glm::vec3& offset);
    void add(Mesh&& mesh, const glm::mat4& model);

    const Mesh& getMesh(int index) const;
    const glm::mat4& getModel(int index) const;
};

#endif //MINECRAFT_MESHHEAP_H