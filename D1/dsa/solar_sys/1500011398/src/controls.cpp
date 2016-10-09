#include "controls.h"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}

// Initial position : on +Z
glm::vec3 position = glm::vec3(0, 0, 5);

// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;

// Initial vertical angle : none
float verticalAngle = 0.0f;

// Initial Field of View
// 45.0 has a good vision
float initialFoV = 45.0f;

// 3 units / second
float speed = 3.0f; 
float mouseSpeed = 0.005f;

void computeMatricesFromInputs(planet *fix_planet) {

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);


	// the function of H, L, J, K is the same as mouse move
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		xpos -= 5;

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		xpos += 5;

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		ypos += 5;

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		ypos -= 5;

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	if (!fix_planet) {
		// Move forward
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += direction * deltaTime * speed;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position -= direction * deltaTime * speed;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			position += right * deltaTime * speed;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position -= right * deltaTime * speed;
		}
	} else {
		// if the is_fixed is true
		// fix the position at the position of the planet
		position = glm::vec3(fix_planet->get_x(), 
			fix_planet->get_y(), fix_planet->get_z());
	}

	float FoV = initialFoV;

	// Projection matrix
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	
	// Camera matrix
	ViewMatrix = glm::lookAt(position, position + direction, up);

	// press Q to accelerate the speed
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		speed *= 1.1f;

	// press E to slow the speed
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		speed /= 1.1f;

	lastTime = currentTime;
}