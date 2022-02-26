#include "Light.h"
#include <sstream>
#include <string>
/*
class Derived: public Base
{
public:
    Derived(int value)
        : Base { value }
    {
    }

    int getValue() const  { return m_value; }

    void identify() const
    {
        Base::identify(); // call Base::identify() first
        std::cout << "I am a Derived\n"; // then identify ourselves
    }
};
*/
Light::Light() : ambient(glm::vec3(0.2f, 0.2f, 0.2f)),
diffuse(glm::vec3(0.7f, 0.7f, 0.7f)),
specular(glm::vec3(1.0f, 1.0f, 1.0f)),
constant(1.0f),
linear(0.09f),
quadratic(0.032f) {

}

void Light::setLightColors(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void Light::setLightAttenuation(float constant, float linear, float quadratic) {
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

void Light::useLightProperties(Shader& shader) {
    shader.setVec3(getPropertyName("ambient"), ambient);
    shader.setVec3(getPropertyName("diffuse"), diffuse);
    shader.setVec3(getPropertyName("specular"), specular);

    shader.setFloat(getPropertyName("constant"), constant);
    shader.setFloat(getPropertyName("linear"), linear);
    shader.setFloat(getPropertyName("quadratic"), quadratic);
}


std::string Light::getPropertyName(const std::string& propertyName) const {
    std::stringstream ss;
    ss << uniformName << "." << propertyName;
    std::string s = ss.str();
    return s;
}

PositionalLight::PositionalLight(std::string name, const glm::vec3 position) : position(position), uniformName(std::move(name)) {}

void PositionalLight::use(Shader& shader) {
    useLightProperties(shader);
    shader.setVec3(getPropertyName("position"), position);
}

DirectionalLight::DirectionalLight(std::string name, const glm::vec3 direction) : direction(direction), uniformName(std::move(name)) {}

void DirectionalLight::use(Shader& shader) {
    useLightProperties(shader);
    shader.setVec3(getPropertyName("direction"), direction);
}