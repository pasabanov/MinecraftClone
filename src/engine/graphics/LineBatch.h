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

class LineBatch {

	inline static const std::vector<int> VERTEX_ATTRS = { 3, 4, 0 };
	inline static const uint VERTEX_SIZE = std::accumulate(VERTEX_ATTRS.begin(), VERTEX_ATTRS.end(), 0);

	Mesh mMesh;
	std::vector<float> mBuffer;

public:

	void line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color = { 1, 1, 1, 1 });

	void box(glm::vec3 pos, const glm::vec3& size, const glm::vec4& color = { 1, 1, 1, 1 });

	void clearBuffer();

	void render();

	void draw() const;
};