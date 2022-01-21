#include "Shader.h"



Shader::Shader(uint id) : mId(id) {}



Shader::~Shader() {
    glDeleteProgram(mId);
}



void Shader::load(const std::string& vertexFile, const std::string& fragmentFile) {

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try {

        vShaderFile.open(vertexFile);
        fShaderFile.open(fragmentFile);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch(const std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;

        throw ShaderCreationException();
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    uint vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "SHADER::VERTEX: compilation failed\n";
        std::cerr << infoLog << '\n';

        throw ShaderCreationException();
    }

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "SHADER::FRAGMENT: compilation failed\n";
        std::cerr << infoLog << '\n';

        glDeleteShader(vertex);

        throw ShaderCreationException();
    }

    uint id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "SHADER::PROGRAM: linking failed\n";
        std::cerr << infoLog << '\n';

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(id);

        throw ShaderCreationException();
    }

    glDetachShader(id, vertex);
    glDetachShader(id, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    mId = id;
}



void Shader::use() const {
    glUseProgram(mId);
}



void Shader::uniformMatrix(const std::string& name, const glm::mat4& matrix) const {
    uint transformLoc = glGetUniformLocation(mId, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, false, glm::value_ptr(matrix));
}