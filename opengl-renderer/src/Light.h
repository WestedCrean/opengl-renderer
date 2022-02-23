#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Light {
    public:
    virtual void use(Shader& shader) = 0;
    void setLightColors(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void setLightAttenuation(float constant, float linear, float quadratic);
    void setUniformName(std::string name);

    std::string uniformName;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
};


class PositionalLight : public Light {
    public:
    glm::vec3 position;

    PositionalLight(glm::vec3 position);
    void use(Shader& shader);
};

class DirectionalLight : public Light {
    public:
    glm::vec3 direction;

    DirectionalLight(glm::vec3 direction);
    void use(Shader& shader);
};