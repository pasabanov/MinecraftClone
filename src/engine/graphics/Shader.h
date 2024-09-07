#pragma once

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