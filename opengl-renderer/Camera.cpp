#include "src/Camera.h"

Camera::Camera(glm::vec3 position, float fov) {
	this->position = position;
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->yaw = 0.0;
	this->pitch = 0.0;
	this->fov = fov;

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

void Camera::ProcessKeyboard(Direction direction, float deltaTime) {
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
}


//void Camera::ProcessMouseMovement(float offsetX, float offsetY);
//void Camera::ProcessMouseScroll(float offsetY);