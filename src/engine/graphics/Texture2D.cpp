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

#include <engine/graphics/Texture2D.h>

void Texture2D::glDelete() {
	glDeleteTextures(1, &mId);
}

Texture2D::Texture2D(uint id, uint width, uint height) : mId(id), mWidth(width), mHeight(height) {}

Texture2D::Texture2D(Texture2D&& other) noexcept : mId(other.mId), mWidth(other.mWidth), mHeight(other.mHeight) {
	other.mId = other.mWidth = other.mHeight = GL_NONE;
}

Texture2D::~Texture2D() {
	glDelete();
}

Texture2D& Texture2D::operator=(Texture2D&& other) {
	glDelete();

	mId = other.mId;
	mWidth = other.mWidth;
	mHeight = other.mHeight;

	other.mId = other.mWidth = other.mHeight = GL_NONE;

	return *this;
}

void Texture2D::load(const std::string& filename) {

	uchar* image = SOIL_load_image(
			filename.c_str(),
			(int*)&mWidth,
			(int*)&mHeight,
			nullptr,
			SOIL_LOAD_RGBA);

	for (uint j = 0; j < mHeight/2; ++j) {
		for (uint i = 0; i < mWidth; ++i) {
			uint& pixel1 = ((uint*)(image))[j*mWidth+i];
			uint& pixel2 = ((uint*)(image))[(mHeight-1-j)*mWidth+i];
			uint tmp = pixel1;
			pixel1 = pixel2;
			pixel2 = tmp;
		}
	}

	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			mWidth,
			mHeight,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 5);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);

	SOIL_free_image_data(image);
}

void Texture2D::bind() const {
	glBindTexture(GL_TEXTURE_2D, mId);
}