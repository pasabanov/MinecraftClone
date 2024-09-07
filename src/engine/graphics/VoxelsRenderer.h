#pragma once

#include <headers/includes.h>

#include <engine/graphics/MeshHeap.h>
#include <engine/voxel/ChunkHeap.h>

class VoxelsRenderer {

	inline static const std::vector<int> VERTEX_ATTRS = {
			3, // x, y, z
			2, // texture coords
			4, // r g b s
			0, // null-terminator
	};
	inline static const uint VERTEX_SIZE = std::accumulate(VERTEX_ATTRS.begin(), VERTEX_ATTRS.end(), 0);

	std::vector<float> mBuffer;

	void writeVertex(float x, float y, float z, float u, float v, float r, float g, float b, float s);

public:

	VoxelsRenderer(uint startCapacity = 1024);

	Mesh render(const ChunkHeap& chunks, int chX, int chY, int chZ);

	MeshHeap render(ChunkHeap& chunks);

	void render(ChunkHeap& chunks, MeshHeap& meshes);
};