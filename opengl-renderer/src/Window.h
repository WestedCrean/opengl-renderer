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
    GLFWwindow* m_Window;
    Scene scene;

    Window(int width, int height, std::string title);
    ~Window();

    void setScene(Scene& scene);
    void draw();

    private:
    GLFWwindow* getContext();
    void calculateDeltaTime();

    void processInput();
    void framebufferSizeCallback(int width, int height);
    void mouseCallback(double xposIn, double yposIn);
    void scrollCallback(double xoffset, double yoffset);

    static void static_framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void static_mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void static_scrollCallback(GLFWwindow* window, double xoffset, double yoffset);


    float lastMousePosX = width / 2.0f;
    float lastMousePosY = height / 2.0f;
    bool pristineMouse = true;

};

