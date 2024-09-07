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