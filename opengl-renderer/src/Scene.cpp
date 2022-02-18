#include "Scene.h"

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>
#include <string> 
#include <format>

#include "Shader.h"
#include "Object.h"

Scene::Scene() : camera(glm::vec3(0.0f, 0.0f, 0.0f), 45.0f), background(glm::vec3(0.3f, 0.3f, 0.3f)) {};
Scene::Scene(Camera camera) : camera(camera), background(glm::vec3(0.3f, 0.3f, 0.3f)) {};

void Scene::setBackgroundColor(glm::vec3 background) {
    this->background = background;
}

void Scene::addObject(Object& object) {
    objects.push_back(object);
}

void Scene::setupTestScene() {

    // positions of the point lights
    pointLightPositions = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };

    // test cube model
    objects.push_back(Object("./models/cube/test_cube.obj"));

    shaders.push_back(Shader("./shaders/cube.vert", "./shaders/cube.frag"));
}

bool Scene::wasSetUp() {
    return !objects.empty() && !shaders.empty();
}

void Scene::draw() {
    glClearColor(background.x, background.y, background.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!wasSetUp()) {
        // scene was not set up
        return;
    }
    Shader shader = shaders[0];

    shader.use();
    // shader uniforms
    for (unsigned int i = 0; i < pointLightPositions.size(); i++) {
        shader.setVec3("pointLights[0].position", pointLightPositions[i]);
        shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("pointLights[0].diffuse", 1.0f, 0.66f, 0.24f);
        shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[0].constant", 1.0f);
        shader.setFloat("pointLights[0].linear", 0.09f);
        shader.setFloat("pointLights[0].quadratic", 0.032f);
    }

    int SCR_WIDTH = 800;
    int SCR_HEIGHT = 600;

    shader.setVec3("viewPos", camera.position);
    shader.setFloat("material.shininess", 32.0f);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.getViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
    shader.setMat4("model", model);

    for (Object& object : objects) {
        object.draw(shader);
    }
}