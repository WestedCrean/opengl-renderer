#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"

struct StringHelper {
    const char* p;
    StringHelper(const std::string& s) : p(s.c_str()) {}
    operator const char** () { return &p; }
};

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    unsigned int vertexHandle;
    unsigned int fragmentHandle;
    std::string vertexCode = readShaderCode(vertexPath);
    std::string fragmentCode = readShaderCode(fragmentPath);

    compileShader(vertexHandle, vertexCode.c_str(), GL_VERTEX_SHADER);
    compileShader(fragmentHandle, fragmentCode.c_str(), GL_FRAGMENT_SHADER);

    linkShader(vertexHandle, fragmentHandle);

    glDeleteShader(vertexHandle);
    glDeleteShader(fragmentHandle);
}

std::string Shader::readShaderCode(const std::string& path) {
    std::string shaderCode;
    std::ifstream shaderFile;

    // ensure ifstream objects can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return shaderCode;
}

void Shader::compileShader(unsigned int& shaderHandle, const char* shaderCode, int shaderType) {
    int success;
    char infoLog[512];

    shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &shaderCode, NULL);
    glCompileShader(shaderHandle);

    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
        std::string shaderString = shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << shaderString << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::linkShader(unsigned int& vertexHandle, unsigned int& fragmentHandle) {
    int success;
    char infoLog[512];

    id = glCreateProgram();
    glAttachShader(id, vertexHandle);
    glAttachShader(id, fragmentHandle);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

}

// use/activate the shader
void Shader::use() {
    glUseProgram(id);
}

// uniforms setters
void Shader::setBool(std::string name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(std::string name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(std::string name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setMat4(std::string name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setVec3(std::string name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
void Shader::setVec3(std::string name, glm::vec3 vector) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), vector.x, vector.y, vector.z);
}