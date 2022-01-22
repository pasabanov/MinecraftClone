#ifndef MINECRAFT_SHADER_H
#define MINECRAFT_SHADER_H

#include "../headers/includes.h"

class Shader {

    uint mId;

    void uniformMatrix(const std::string& name, const glm::mat4& matrix) const;

public:

    class ShaderCreationException : public std::exception {};

    explicit Shader(uint id = (uint)-1);
    Shader(Shader&& other);

    ~Shader();

    Shader& operator=(Shader&& other);

    void load(const std::string& vertexFilename, const std::string& fragmentFilename);

    void setModel(const glm::mat4& model) const;

    void setProjView(const glm::mat4& projview) const;

    void use() const;
};

#endif //MINECRAFT_SHADER_H