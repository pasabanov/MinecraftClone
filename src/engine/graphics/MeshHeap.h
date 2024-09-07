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