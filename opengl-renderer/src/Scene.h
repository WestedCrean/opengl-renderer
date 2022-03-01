#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Camera.h"
#include "Light.h"
#include "Object.h"

class Scene {
    public:
    Camera camera;
    glm::vec3 background;
    std::vector<PositionalLight> posLights;
    std::vector<Object> objects;
    std::vector<Shader> shaders;

    Scene();
    Scene(Camera camera);

    void addPosLight(PositionalLight& light);
    void addObject(Object& object);
    void setBackgroundColor(glm::vec3 background);
    void setupTestScene();
    bool wasSetUp();
    void draw();
};

