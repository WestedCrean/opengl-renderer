#pragma once
#include <glm/glm.hpp>
#include "Camera.h"

class Scene {
    public:
    Camera camera;
    glm::vec3 background;

    Scene();
    Scene(Camera camera);

    void addObject(/* Object object*/);
    void setBackgroundColor(glm::vec3 background);
    void draw();
};

