#ifndef CONTROLS
#define CONTROLS

#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "planet.h"

extern GLFWwindow* window;

// as its name, this function will set projection matrix by
// the input of the keyboard and mouse
void computeMatricesFromInputs(planet *fix_planet = nullptr);

// return the ViewMatrix
glm::mat4 getViewMatrix();

// return the ProjectionMatrix
glm::mat4 getProjectionMatrix();

#endif