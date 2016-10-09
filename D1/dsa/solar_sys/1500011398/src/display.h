#ifndef DISPLAY
#define DISPLAY

//include strandred libraries
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <strstream>

//include GLEW
#include <glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

//include sth wrote by me
#include "shader.h"
#include "texture.h"
#include "controls.h"
#include "objloader.h"
#include "planet.h"
#include "update.h"
#include "text2D.h"
#include "hashtable.h"
#include "AVL.h"

// this function will render the solar system on the screen
void display(std::vector<planet *> all_planet);

// print_text is used to print sth on the screen
inline void print_text(const int &last_time, const int &step,
	const int &period, const double &sun_GM);

// add a planet
inline void add_planet(std::vector<planet *> &all_planet);

#endif