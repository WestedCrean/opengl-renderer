#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "Window.h"
#include "Camera.h"
#include "Direction.h"


Window::Window(int width, int height, std::string title) {
    // initialize and create a window context
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Unable to create a window context");
    }
    // register callback in case window size changes

    // we have to translate our functions to static functions
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    glfwTerminate();
}

GLFWwindow* Window::getContext() {
    return window;
}

void Window::setScene(Scene& scene) {
    this->scene = scene;
}

void Window::draw() {
    while (!glfwWindowShouldClose(window)) {
        // calculate frame time
        calculateDeltaTime();

        // process inputs
        processInput(window);

        scene.setBackgroundColor(glm::vec3(0.17f, 0.23f, 0.40f));
        scene.draw();

        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::calculateDeltaTime() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Window::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        scene.camera.processKeyboard(Direction::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        scene.camera.processKeyboard(Direction::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        scene.camera.processKeyboard(Direction::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        scene.camera.processKeyboard(Direction::RIGHT, deltaTime);
}

void Window::mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (pristineMouse) {
        lastMousePosX = xpos;
        lastMousePosY = ypos;
        pristineMouse = false;
    }

    float xoffset = xpos - lastMousePosX;
    float yoffset = lastMousePosY - ypos; // reversed since y-coordinates go from bottom to top

    lastMousePosX = xpos;
    lastMousePosY = ypos;

    scene.camera.processMouseMovement(xoffset, yoffset);
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    scene.camera.processMouseScroll(static_cast<float>(yoffset));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void Window::setMouseMoveCallback() {


    glfwSetCursorPosCallback(window, mouse_callback);


    glfwSetWindowUserPointer(window, windowPtr);

    auto func = [](GLFWwindow* w, int width, int height)
    {
        static_cast<Window*>(glfwGetWindowUserPointer(w))->mouseCallback(w, width, height);
    };

    glfwSetCursorPosCallback(window, func);
}

void Window::setMouseScrollCallback() {
    glfwSetWindowUserPointer(window, windowPtr);

    auto func = [](GLFWwindow* w, int x, int y)
    {
        static_cast<Window*>(glfwGetWindowUserPointer(w))->scrollCallback(w, x, y);
    };
    
    glfwSetScrollCallback(window, func);
}

void setFramebufferSizeCallback() {
    glfwSetWindowUserPointer(window, windowPtr);

    auto func = [](GLFWwindow* w, int width, int height)
    {
        static_cast<Window*>(glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, width, height);
    };

    glfwSetFramebufferSizeCallback(window, func);
}
