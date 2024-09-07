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

#include <engine/graphics/LineBatch.h>

void LineBatch::line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color) {

	mBuffer.push_back(start.x);
	mBuffer.push_back(start.y);
	mBuffer.push_back(start.z);
	mBuffer.push_back(color.r);
	mBuffer.push_back(color.g);
	mBuffer.push_back(color.b);
	mBuffer.push_back(color.a);

	mBuffer.push_back(end.x);
	mBuffer.push_back(end.y);
	mBuffer.push_back(end.z);
	mBuffer.push_back(color.r);
	mBuffer.push_back(color.g);
	mBuffer.push_back(color.b);
	mBuffer.push_back(color.a);
}

void LineBatch::box(glm::vec3 pos, const glm::vec3& size, const glm::vec4& color) {

	glm::vec3 vecX = glm::vec3(size.x, 0, 0);
	glm::vec3 vecY = glm::vec3(0, size.y, 0);
	glm::vec3 vecZ = glm::vec3(0, 0, size.z);

	line(pos, pos + vecX, color);
	line(pos, pos + vecY, color);
	line(pos, pos + vecZ, color);

	pos += vecX;

	line(pos, pos + vecY, color);
	line(pos, pos + vecZ, color);

	pos += vecY - vecX;

	line(pos, pos + vecX, color);
	line(pos, pos + vecZ, color);

	pos += vecZ - vecY;

	line(pos, pos + vecX, color);
	line(pos, pos + vecY, color);

	pos += size - vecZ;

	line(pos, pos - vecX, color);
	line(pos, pos - vecY, color);
	line(pos, pos - vecZ, color);
}

void LineBatch::clearBuffer() {
	mBuffer.resize(0);
}

void LineBatch::render() {
	mMesh.create(mBuffer.data(), mBuffer.size() / VERTEX_SIZE, VERTEX_ATTRS.data());
}

void LineBatch::draw() const {
	mMesh.draw(GL_LINES);
}