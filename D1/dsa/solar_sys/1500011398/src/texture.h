#ifndef TEXTURE
#define TEXTURE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <random>
#include <ctime>
#include <glew.h>
#include <glfw3.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

// DDS loader
GLuint loadDDS(const char * imagepath);

#endif