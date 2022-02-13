#pragma once
#include <glm/glm.hpp>
#include "Direction.h"

class Camera {
public:
	float fov;
	//glm::mat4 view;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	float yaw;
	float pitch;

	Camera(glm::vec3 position, float fov);

	glm::mat4 getViewMatrix();

	void lookAt(glm::vec3 target);
	void ProcessKeyboard(Direction direction, float deltaTime);
	void ProcessMouseMovement(float offsetX, float offsetY);
	void ProcessMouseScroll(float offsetY);
private:
	float lastFrameTime;
};