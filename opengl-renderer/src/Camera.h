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
	void processKeyboard(Direction direction, float deltaTime);
	void processMouseMovement(float offsetX, float offsetY);
	void processMouseScroll(float offsetY);
private:
	float lastFrameTime;
};