#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Light {
    public:
    Light();
    virtual void use(Shader& shader) = 0;
    void setLightColors(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular);
    void setLightAttenuation(float constant, float linear, float quadratic);
    void setUniformName(const std::string& name);
    void useLightProperties(Shader& shader);
    std::string getPropertyName(const std::string& propertyName) const;

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
    const std::string uniformName;

    PositionalLight(std::string name, const glm::vec3 position);
    void use(Shader& shader);
};

class DirectionalLight : public Light {
    public:
    glm::vec3 direction;
    const std::string uniformName;

    DirectionalLight(std::string name, const glm::vec3 direction);
    void use(Shader& shader);
};