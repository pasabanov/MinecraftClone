#pragma once

/*
 * MinecraftClone
 * Copyright (C) © 2022  Petr Alexandrovich Sabanov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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