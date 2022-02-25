#include "Light.h"



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

void Light::setLightColors(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}
void Light::setLightAttenuation(float constant, float linear, float quadratic) {
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}
void Light::setUniformName(std::string name) {
    this->uniformName = name;
}

PositionalLight::PositionalLight(glm::vec3 position) {}
void PositionalLight::use(Shader& shader) {}

DirectionalLight::DirectionalLight(glm::vec3 direction) {}
void DirectionalLight::use(Shader& shader) {}