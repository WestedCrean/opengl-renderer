#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include "Scene.h"

class Window {

    public:

    float deltaTime;
    float lastFrame;
    int width;
    int height;
    GLFWwindow* window;
    Window* windowPtr;
    Scene scene;

    Window(int width, int height, std::string title);
    ~Window();
    GLFWwindow* getContext();

    void setScene(Scene& scene);

    void draw();
    void calculateDeltaTime();
    void processInput(GLFWwindow* window);
    void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void setMouseMoveCallback();
    void setMouseScrollCallback();
    void setFramebufferSizeCallback();

private:
    float lastMousePosX = width / 2.0f;
    float lastMousePosY = height / 2.0f;
    bool pristineMouse = true;

};

