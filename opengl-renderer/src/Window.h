#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {

    public:

    Window(int width, int height, std::string title);
    GLFWwindow* getContext();

    private:
    GLFWwindow* window;
};

