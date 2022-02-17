#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include "Scene.h"

class Window {

    public:

    float deltaTime;
    float lastFrame;
    GLFWwindow* window;
    Scene scene;

    Window(int width, int height, std::string title);
    ~Window();
    GLFWwindow* getContext();

    void setScene(Scene& scene);

    void draw();
    void calculateDeltaTime();
    void processInput(GLFWwindow* window);
    void ProcessMouseMovement(float offsetX, float offsetY);
    void ProcessMouseScroll(float offsetY);

};

