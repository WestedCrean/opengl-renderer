#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include "Shader.h"

struct StringHelper {
  const char *p;
  StringHelper(const std::string& s) : p(s.c_str()) {}
  operator const char**() { return &p; }
};

Shader::Shader(std::string& vertexPath, std::string& fragmentPath) {
	// read
}

// use/activate the shader
void Shader::use() {
	glUseProgram(id);
}

// uniforms setters
void Shader::setBool(std::string& name, bool value) const { 
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setMat4(std::string& name, glm::mat4 value) const { 
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setVec3(std::string& name, float x, float y, float z) const { 
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
void Shader::setVec3(std::string& name, glm::vec3 vector) const {
	glUniform3f(glGetUniformLocation(id, name.c_str()), vector.x, vector.y, vector.z);
}