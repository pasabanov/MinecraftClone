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

class Mesh {

	uint mVAO = GL_NONE, mVBO = GL_NONE;
	uint mVerticesCount = 0;

	void glDelete();

public:

	Mesh();
	Mesh(const float* buffer, uint verticesCount, const int* attrs);
	Mesh(Mesh&& other) noexcept;

	~Mesh();

	Mesh& operator=(Mesh&& other) noexcept;

	void create(const float* buffer, uint verticesCount, const int* attrs);

	void draw(uint primitive = GL_TRIANGLES) const;
};