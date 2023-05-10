#include <engine/graphics/Shader.h>



void Shader::glDelete() {
    glDeleteProgram(mId);
}



void Shader::uniformMatrix(const std::string& name, const glm::mat4& matrix) const {
    uint transformLoc = glGetUniformLocation(mId, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, false, glm::value_ptr(matrix));
}



Shader::Shader(uint id) : mId(id) {}

Shader::Shader(Shader&& other) : mId(other.mId) {
    other.mId = GL_NONE;
}



Shader::~Shader() {
    glDelete();
}



Shader& Shader::operator=(Shader&& other) {

    glDelete();

    mId = other.mId;

    other.mId = GL_NONE;

    return *this;
}



void Shader::load(const std::string& vertexFilename, const std::string& fragmentFilename) {

    glDelete();

    std::string strVertexCode;
    std::string strFragmentCode;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    vertexFile.exceptions(std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::badbit);

    try {

        vertexFile.open(vertexFilename);
        fragmentFile.open(fragmentFilename);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vertexFile.rdbuf();
        fShaderStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        strVertexCode = vShaderStream.str();
        strFragmentCode = fShaderStream.str();

    } catch (const std::ifstream::failure& e) {
        throw ShaderCreationException("File not successfully read");
    }

    const char* vertexCode = strVertexCode.c_str();
    const char* fragmentCode = strFragmentCode.c_str();

    uint vertex, fragment;
    int success;
    int infoLogBuffSize = 1024;
    char infoLogBuff[infoLogBuffSize];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, infoLogBuffSize, nullptr, infoLogBuff);

        std::string message = "Vertex : compilation failed:\n";
        message.append(infoLogBuff);
        throw ShaderCreationException(message);
    }

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, infoLogBuffSize, nullptr, infoLogBuff);

        glDeleteShader(vertex);

        std::string message = "Fragment : compilation failed:\n";
        message.append(infoLogBuff);
        throw ShaderCreationException(message);
    }

    mId = glCreateProgram();
    glAttachShader(mId, vertex);
    glAttachShader(mId, fragment);
    glLinkProgram(mId);

    glGetProgramiv(mId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(mId, infoLogBuffSize, nullptr, infoLogBuff);

        glDetachShader(mId, vertex);
        glDetachShader(mId, fragment);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(mId);

        std::string message = "Shader : program linking failed:\n";
        message.append(infoLogBuff);
        throw ShaderCreationException(message);
    }

    glDetachShader(mId, vertex);
    glDetachShader(mId, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}



void Shader::setModel(const glm::mat4& model) const {
    uniformMatrix("model", model);
}



void Shader::setProjView(const glm::mat4& projview) const {
    uniformMatrix("projview", projview);
}



void Shader::use() const {
    glUseProgram(mId);
}