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

#include <engine/graphics/Mesh.h>

void Mesh::glDelete() {
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

Mesh::Mesh() {}

Mesh::Mesh(const float* buffer, uint verticesCount, const int* attrs) {
	create(buffer, verticesCount, attrs);
}

Mesh::Mesh(Mesh&& other) noexcept
: mVAO(other.mVAO), mVBO(other.mVBO), mVerticesCount(other.mVerticesCount) {
	other.mVAO = other.mVBO = other.mVerticesCount = GL_NONE;
}

Mesh::~Mesh() {
	glDelete();
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {

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
	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
}