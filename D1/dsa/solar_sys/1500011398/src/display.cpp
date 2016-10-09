#include "display.h"

GLFWwindow *window;

void display(std::vector<planet *> all_planet) {
	
	// Initialise GLFW
	assert(glfwInit());

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(800, 600, "Solar_System", nullptr, nullptr);
	assert(window != nullptr);

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	assert(glewInit() == GLEW_OK);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", 
		"TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Load the texture
	std::vector<GLuint> Texture_vec;
	std::string path_prefix = "DDS\\", path_postfix = ".DDS";
	for (auto c : all_planet) {
		std::string path = path_prefix + c->get_name() + path_postfix;
		Texture_vec.push_back(loadDDS(&path[0]));
	}

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Load the obj of a sphere
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	loadOBJ("sphere.obj", temp_vertices, temp_uvs, temp_normals);

	// all the planet can use the same obj
	std::vector<std::vector<glm::vec3> > vertices(all_planet.size(), temp_vertices);
	std::vector<std::vector<glm::vec2> > uvs(all_planet.size(), temp_uvs);
	std::vector<std::vector<glm::vec3> > normals(all_planet.size(), temp_normals);
	
	// Load it into a VBO
	std::vector<GLuint> vertexbuffer;
	std::vector<GLuint> uvbuffer;

	for (int i = 0; i < all_planet.size(); ++i) {
		GLuint tmp_vertexbuffer;
		glGenBuffers(1, &tmp_vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, tmp_vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices[i].size() * sizeof(glm::vec3),
			&vertices[i][0], GL_STATIC_DRAW);
		vertexbuffer.push_back(tmp_vertexbuffer);

		GLuint tmp_uvbuffer;
		glGenBuffers(1, &tmp_uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, tmp_uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs[i].size() * sizeof(glm::vec2), 
			&uvs[i][0], GL_STATIC_DRAW);
		uvbuffer.push_back(tmp_uvbuffer);
	}

	// Holstein is a DDS of the fonts
	initText2D("DDS\\Holstein.DDS");

	// create a hashtable contains all planets
	bintree<std::string, planet *> planet_bintree;
	for (auto c : all_planet)
		planet_bintree.add(c->get_name(), c);

	int ok_resize = 1;

	if (ok_resize)
		for (auto c : all_planet)
			if (c->get_name() != "sun")
				c->get_radius() *= 1500;
			else
				c->get_radius() *= 50;
#ifndef USE_HASHTABLE
	double step(256), period(32768);
#else
	double step(8), period(256);
#endif
	bool pause = false;
	int pause_time = time(nullptr);
	int planet_create_time = 0;
	
	planet *fix_planet = nullptr;

	std::fstream file_out("out.xls", fstream::app);
	updater n_updater(all_planet);

	int last_time(0);

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs(fix_planet);
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 P_V_Matrix = ProjectionMatrix * ViewMatrix;
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		for (int i = 0; i < all_planet.size(); ++i) {
			glm::mat4 tmp_ModelMatrix = 
				glm::translate(glm::vec3(all_planet[i]->get_x(), all_planet[i]->get_y(), all_planet[i]->get_z())) *
				glm::scale(glm::vec3(all_planet[i]->get_radius(), all_planet[i]->get_radius(), all_planet[i]->get_radius()));
			glm::mat4 tmp_MVP = P_V_Matrix * tmp_ModelMatrix;

			// Send transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmp_MVP[0][0]);

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture_vec[i]);
			// Set our "myTextureSampler" sampler to user Texture Unit 0
			glUniform1i(TextureID, 0);

			// 1rst attribute buffer : vertices
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 2nd attribute buffer : UVs
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[i]);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// Draw
			glDrawArrays(GL_TRIANGLES, 0, vertices[i].size());
		}
		
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
			if (step < period/1.04)
				step *= 1.04;
		}

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			if (step < period*1.04 && step > 1)
				step /= 1.04;
		}

		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
			if (step < period*1.04)
				period *= 1.04;
		}

		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
			if (step < period/1.04)
				period /= 1.04;
		}

		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !fix_planet) {
			std::string fix_planet_name;
			do {
				std::cin >> fix_planet_name;
				fix_planet = planet_bintree[fix_planet_name];
			} while (!fix_planet);
		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			fix_planet = nullptr;
		}

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			if (time(nullptr) - pause_time > 1) {
				pause = !pause;
				pause_time = time(nullptr);
			}
		}

		// print the coordinates of all the planets
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS &&
			time(nullptr) - pause_time > 1) {
			for (auto c : all_planet) {
#ifndef USE_HASHTABLE
				std::cerr << c->get_name() << ' ';
				c->printcoor(std::cerr, last_time / 86400) << std::endl;
#else
				c->printcoor(file_out, last_time / 86400) << std::endl;
#endif
			}
			pause_time = time(nullptr);
			std::cerr << std::endl;
		}

		if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
			all_planet[0]->get_GM() /= 1.02;

		if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
			all_planet[0]->get_GM() *= 1.02;

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS &&
			planet_create_time < last_time) {

			planet_create_time = last_time + 10 * period / step * step;

			add_planet(all_planet);
			n_updater.add_planet(all_planet[all_planet.size() - 1]);

			// update the AVL bintree
			planet_bintree.add(all_planet[all_planet.size() - 1]->get_name(),
				all_planet[all_planet.size() - 1]);

			std::string path = path_prefix +
				all_planet[all_planet.size() - 1]->get_name() +
				path_postfix;
			Texture_vec.push_back(loadDDS(&path[0]));

			vertices.push_back(temp_vertices);
			uvs.push_back(temp_uvs);
			normals.push_back(temp_normals);

			GLuint tmp_vertexbuffer;
			glGenBuffers(1, &tmp_vertexbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, tmp_vertexbuffer);
			glBufferData(GL_ARRAY_BUFFER, vertices[all_planet.size() - 1].size()
				* sizeof(glm::vec3),
				&vertices[all_planet.size() - 1][0], GL_STATIC_DRAW);
			vertexbuffer.push_back(tmp_vertexbuffer);

			GLuint tmp_uvbuffer;
			glGenBuffers(1, &tmp_uvbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, tmp_uvbuffer);
			glBufferData(GL_ARRAY_BUFFER, uvs[all_planet.size() - 1].size()
				* sizeof(glm::vec2),
				&uvs[all_planet.size() - 1][0], GL_STATIC_DRAW);
			uvbuffer.push_back(tmp_uvbuffer);

			if (ok_resize)
				all_planet[all_planet.size() - 1]->get_radius() *= 1500;
		}

		if (!pause) {
			last_time += step * (period / step);
			n_updater.work(step, period);
		}

		if (fix_planet && last_time % (int)(step + 1) < (step/1)) 
			fix_planet->printcoor(cout, last_time / 86400) << std::endl;

		print_text(last_time, step, period, all_planet[0]->get_GM());

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	for (auto c : vertexbuffer) {
		glDeleteBuffers(1, &c);
	}
	
	for (auto c : uvbuffer) {
		glDeleteBuffers(1, &c);
	}

	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void print_text(const int &last_time, const int &step,
	const int &period, const double &sun_GM) {
	std::string display_time;
	std::strstream ss;
	std::string year, day, hour, string_step, string_period;
	ss << last_time / 31536000;
	ss >> year;
	ss.clear();
	ss << last_time % 31536000 / 86400;
	ss >> day;
	ss.clear();
	display_time = year + "year(s)" + day + "day(s)";
	printText2D(&display_time[0], 0, 90, 30);

	std::string display_step_period;
	ss << step;
	ss >> string_step;
	ss.clear();
	ss << period;
	ss >> string_period;
	ss.clear();

	printText2D(&("step     : " + string_step)[0], 0, 30, 30);
	printText2D(&("period   : " + string_period)[0], 0, 0, 30);

	std::string display_sun_mass;
	ss << sun_GM / 3.9696e-14;
	ss >> display_sun_mass;
	printText2D(&("sun mass : " + display_sun_mass)[0], 0, 60, 30);
}

void add_planet(std::vector<planet *> &all_planet) {
	std::cerr << "Create a planet.." << std::endl;
	std::cerr << "The weight of the planet?" 
		" ( the mass of earth is 1 )" << std::endl;
	double n_mass;
	std::cin >> n_mass;

	std::cerr << "What's the name?" << std::endl;
	std::string planet_name;
	std::cin >> planet_name;
	
	std::cerr << "the orbit radius? "
		"the orbit radius of the earth is 1" << std::endl;
	double n_d;
	std::cin >> n_d;

	std::cerr << "the incliantion?" << std::endl;
	double n_inclination;
	std::cin >> n_inclination;

	std::cerr << "the radius?"
		"(the radius of the earth is 1)" << std::endl;
	double n_r;
	std::cin >> n_r;

	planet *new_planet = nullptr;

	std::cerr << "which kind of orbit do u wanna get?\n"
		"1 for ellipse\n"
		"2 for parabola" << std::endl;
	int index;
	std::cin >> index;
	switch (index) {
	case 1:
		new_planet = new planet(planet_name, n_d,
			n_inclination, 0, n_r, n_mass, all_planet[0]);
		break;
	default:
		new_planet = new planet(planet_name, n_d,
			n_inclination, 1, n_r, n_mass, all_planet[0]);
		break;
	}

	for (int i = 1; i < all_planet.size(); ++i) {
		all_planet[i]->get_interaction_planet().push_back(new_planet);
	}
	all_planet.push_back(new_planet);

	new_planet->get_layer() = 0;
}