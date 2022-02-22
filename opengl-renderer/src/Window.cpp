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

    m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_Window) {
        glfwTerminate();
        throw std::runtime_error("Unable to create a window context");
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, this);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glEnable(GL_DEPTH_TEST);


    glfwSetFramebufferSizeCallback(m_Window, static_framebufferSizeCallback);
    glfwSetCursorPosCallback(m_Window, static_mouseCallback);
    glfwSetScrollCallback(m_Window, static_scrollCallback);
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

GLFWwindow* Window::getContext() {
    return m_Window;
}

void Window::setScene(Scene& scene) {
    this->scene = scene;
}

void Window::draw() {
    while (!glfwWindowShouldClose(getContext())) {
        // calculate frame time
        calculateDeltaTime();

        // process inputs
        processInput();

        scene.setBackgroundColor(glm::vec3(0.17f, 0.23f, 0.40f));
        scene.draw();

        // swap buffers
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Window::calculateDeltaTime() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Window::processInput() {
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);

    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        scene.camera.processKeyboard(Direction::FORWARD, deltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        scene.camera.processKeyboard(Direction::BACKWARD, deltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        scene.camera.processKeyboard(Direction::LEFT, deltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        scene.camera.processKeyboard(Direction::RIGHT, deltaTime);
}

void Window::mouseCallback(double xposIn, double yposIn) {
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

void Window::scrollCallback(double xoffset, double yoffset) {
    scene.camera.processMouseScroll(static_cast<float>(yoffset));
}

void Window::framebufferSizeCallback(int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Window::static_framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Window* actualWindow = (Window*)glfwGetWindowUserPointer(window);
    actualWindow->framebufferSizeCallback(width, height);
}

void Window::static_mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    Window* actualWindow = (Window*)glfwGetWindowUserPointer(window);
    actualWindow->mouseCallback(xposIn, yposIn);
}

void Window::static_scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Window* actualWindow = (Window*)glfwGetWindowUserPointer(window);
    actualWindow->scrollCallback(xoffset, yoffset);
}