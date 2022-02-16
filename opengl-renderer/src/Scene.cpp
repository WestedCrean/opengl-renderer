#include "Scene.h"

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



Scene::Scene() : camera(glm::vec3(0.0f, 0.0f, 0.0f), 45.0f), background(glm::vec3(0.3f, 0.3f, 0.3f)) {};
Scene::Scene(Camera camera) : camera(camera), background(glm::vec3(0.3f, 0.3f, 0.3f)) {};

void Scene::setBackgroundColor(glm::vec3 background) {
    this->background = background;
}

void Scene::addObject() {}

void Scene::draw() {
    glClearColor(background.x, background.y, background.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}