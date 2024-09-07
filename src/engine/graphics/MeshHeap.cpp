#include <engine/graphics/MeshHeap.h>

MeshHeap::MeshHeap(int size) : mMeshes(size), mModels(size) {}

int MeshHeap::size() const {
	return mMeshes.size();
}

void MeshHeap::set(Mesh&& mesh, const glm::vec3& offset, int index) {
	glm::mat4 model (1);
	model = glm::translate(model, offset);
	set(std::move(mesh), model, index);
}

void MeshHeap::set(Mesh&& mesh, const glm::mat4& model, int index) {
	mMeshes[index] = std::move(mesh);
	mModels[index] = model;
}

const Mesh& MeshHeap::getMesh(int index) const {
	return mMeshes[index];
}

const glm::mat4& MeshHeap::getModel(int index) const {
	return mModels[index];
}