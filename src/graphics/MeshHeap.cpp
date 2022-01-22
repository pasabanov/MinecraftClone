#include "MeshHeap.h"



MeshHeap::MeshHeap() {}



int MeshHeap::size() const {
    return mMeshes.size();
}



void MeshHeap::add(Mesh&& mesh, const glm::vec3& offset) {
    glm::mat4 model (1);
    model = glm::translate(model, offset);
    add(std::move(mesh), model);
}

void MeshHeap::add(Mesh&& mesh, const glm::mat4& model) {
    mMeshes.push_back(std::move(mesh));
    mModels.push_back(model);
}



const Mesh& MeshHeap::getMesh(int index) const {
    return mMeshes[index];
}

const glm::mat4& MeshHeap::getModel(int index) const {
    return mModels[index];
}