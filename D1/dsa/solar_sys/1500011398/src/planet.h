#ifndef PLANET
#define PLANET

#include <string>
#include <ctime>

#include "queue.h"
#include "hashtable.h"
#include "globals.h"

#ifdef USE_HASHTABLE
#include "hierarchical_indexed.h"
#endif

class planet;
class updater;

void collision(planet *p1, planet *p2);

class planet {
	friend class updater;
	friend void collision(planet *p1, planet *p2);
	// function
public:
	// constructor
	planet(std::string n_name, double n_d, double n_inclination,
		double n_e, double n_radius, double n_mass, planet *n_parent = nullptr);

	// destructor
	~planet();
	
	// calculate the energy and return it
	double energy();
	// calculate the angular momentum  and return it
	double *angular_momentum();
	
	// print the coordinate in the console screen
	// the three bools is used to decided which value will be printed
	std::ostream &printcoor(std::ostream &out,
		int n_day, bool whether_display_x = true,
		bool whether_display_y = true, bool whether_display_z = true,
		bool whether_display_d = true);

	// add a satellite
	planet *add_satellite(std::string n_name, double n_d, double n_inclination,
		double n_e, double n_radius, double n_mass);
	
	// add a satellite using a pointer
	planet *add_satellite(planet *p_satellite);

	// set the interaction_planet vector
	std::vector<planet *> &set_interaction_planet_vector();

#ifdef USE_HASHTABLE
	// calculate the dictionary of the distance and force
	void calculate_dictionary();

	// get the distance_force_dictionary
	hierarchical_index &
		get_distance_force_dictionary() const;
#endif

	// set the value of layer
	void update_layer();
	// using gravitational theory to update the position and velocity
	void update_position_velocity(int step);

	// get sth
	std::vector<planet *> &get_satellite();
	std::vector<planet *> &get_interaction_planet();
	std::vector<planet *> &get_interaction_planet_of_the_same_layer();
	std::string &get_name();
	int &get_layer();

	// use float cuz OpenGL only accepted float
	float get_x();
	float get_y();
	float get_z();

	// this function return the display_radius of the planet
	float &get_radius();

	// return the GM of the planet
	double &get_GM();

	// we don't need to use copy constructor function and
	// assignment function
	planet(planet &P) = delete;

	// record the time of the last collision
	double last_collision_time = 0;

	// data
private:
	// e.g. The parent of the earth is the sun
	planet *m_parent;
	// the name of the planet
	std::string m_name;
	// the position of the planet
	double m_x, m_y, m_z;
	// the velocity of the planet
	double m_vx, m_vy, m_vz;
	// the energy and the angular momtum of the planet
	double m_energy, *m_angular_momentum;
	// the mass of the planet
	double m_mass;
	// the radius of the planet
	double m_radius;

	// the radius that would be displayed in the window
	float display_radius;
	// e.g. the layer of the sun is 1, while that of the earth is 2
	int layer = 0;
	// GM is used to accelerate the calculation
	double GM;

#ifdef USE_HASHTABLE
	// a hash table that contains the distance and the corresopond force
	hierarchical_index *distance_force_dictionary;
#endif

	// satellite is a vector that containes the pointers of its satellite
	std::vector<planet *> satellite;

	// interaction_planet is a vector that containes the pointers of the 
	// planets that need to be counted on in the calculation
	std::vector<planet *> interaction_planet;
	std::vector<planet *> interaction_planet_of_the_same_layer;
};

#endif
