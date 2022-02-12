#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT };

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