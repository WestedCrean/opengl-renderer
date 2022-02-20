#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

#include <iostream>

Camera::Camera(glm::vec3 position, float fov) : position(position), fov(fov) {
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->yaw = 0.0;
    this->pitch = 0.0;

    this->lastFrameTime = 0.0f;
};

void Camera::lookAt(glm::vec3 target) {
    // change front vector to point towards target
    // position + new_front = target  // - position
    // new_front = target - position
    this->front = target - this->position;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(Direction direction, float deltaTime) {
    float cameraSpeed = 2.5f * deltaTime;

    if (direction == Direction::FORWARD) {
        position = position + front * cameraSpeed;
    }
    if (direction == Direction::BACKWARD) {
        position = position - front * cameraSpeed;
    }
    if (direction == Direction::LEFT) {
        position = position - glm::normalize(glm::cross(front, up)) * cameraSpeed;
    }
    if (direction == Direction::RIGHT) {
        position = position + glm::normalize(glm::cross(front, up)) * cameraSpeed;
    }

    std::cout << "Change position: " << "(" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
}


void Camera::processMouseMovement(float offsetX, float offsetY) {
    float sensitivity = 0.1f;
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    yaw = glm::mod(yaw, 360.0f); // clamp yaw

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

    std::cout << "Mouse move" << "(" << offsetX << ", " << offsetY << ")" << std::endl;
}

void Camera::processMouseScroll(float offsetY) {
    fov -= (float)offsetY;
    if (fov < 25.0f)
        fov = 25.0f;
    if (fov > 40.0f)
        fov = 40.0f;
}