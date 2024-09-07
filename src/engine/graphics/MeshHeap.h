#pragma once

#include <headers/includes.h>

#include <engine/graphics/Mesh.h>

class MeshHeap {

	std::vector<Mesh> mMeshes;
	std::vector<glm::mat4> mModels;

public:

	explicit MeshHeap(int size);

	int size() const;

	void set(Mesh&& mesh, const glm::vec3& offset, int index);
	void set(Mesh&& mesh, const glm::mat4& model, int index);

	const Mesh& getMesh(int index) const;
	const glm::mat4& getModel(int index) const;
};