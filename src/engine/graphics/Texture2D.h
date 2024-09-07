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

class Texture2D {

	uint mId = GL_NONE;
	uint mWidth = 0, mHeight = 0;

	void glDelete();

public:

	class TextureCreationException : public MessageException {
	public:
		TextureCreationException(const std::string& message) : MessageException(message) {}
	};

	Texture2D(uint id = GL_NONE, uint width = GL_NONE, uint height = GL_NONE);
	Texture2D(Texture2D&& other) noexcept;

	~Texture2D();

	Texture2D& operator=(Texture2D&& other);

	void load(const std::string& filename);

	void bind() const;
};