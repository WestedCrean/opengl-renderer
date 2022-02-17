#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
    public:

    unsigned int id;

    // constructor reads and builds the shader
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    // use/activate the shader
    void use();

    // uniforms setters
    void setBool(std::string name, bool value) const;
    void setInt(std::string name, int value) const;
    void setFloat(std::string name, float value) const;
    void setMat4(std::string name, glm::mat4 value) const;
    void setVec3(std::string name, float x, float y, float z) const;
    void setVec3(std::string name, glm::vec3 vector) const;

    private:
    std::string readShaderCode(const std::string& path);
    void compileShader(unsigned int& shaderHandle, const char* shaderCode, int shaderType);
    void linkShader(unsigned int& vertexHandle, unsigned int& fragmentHandle);
};

