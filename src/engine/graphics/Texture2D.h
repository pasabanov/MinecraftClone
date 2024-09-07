#pragma once

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