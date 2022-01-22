#ifndef MINECRAFT_SHADER_H
#define MINECRAFT_SHADER_H

#include "../headers/includes.h"

class Shader {

    uint mId;

public:

    class ShaderCreationException : public std::exception {};

    explicit Shader(uint id = (uint)-1);

    ~Shader();

    void load(const std::string& vertexFilename, const std::string& fragmentFilename);

    void use() const;

    void uniformMatrix(const std::string& name, const glm::mat4& matrix) const;
};

#endif //MINECRAFT_SHADER_H