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

#include <engine/exception/MessageException.h>

class Shader {

	uint mId = GL_NONE;

	void glDelete();

	void uniformMatrix(const std::string& name, const glm::mat4& matrix) const;

public:

	class ShaderCreationException : public MessageException {
	public:
		ShaderCreationException(const std::string& message) : MessageException(message) {}
	};

	explicit Shader(uint id = GL_NONE);
	Shader(Shader&& other) noexcept;

	~Shader();

	Shader& operator=(Shader&& other) noexcept;

	void load(const std::string& vertexFilename, const std::string& fragmentFilename);

	void setModel(const glm::mat4& model) const;

	void setProjView(const glm::mat4& projview) const;

	void use() const;
};