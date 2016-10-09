#ifndef UPDATE
#define UPDATE

#include "planet.h"
#include "graph.h"

class updater {
	// function
public:
	// constructor
	updater(const std::vector<planet *> &all_planet);
	
	// we don't need the default constructor
	updater() = delete;

	// update all planets' positions and velocities
	void work(const int step, const int period);

	// add a planet
	void add_planet(planet *new_planet);

	// update the info of the graphs
	void update_graphs();

	// data
private:
	// the planets that needs to be updated
	std::vector<planet *> planets;
	std::vector<std::vector<planet *> > planets_by_layer;
	// counter
	int counter;
	// a graph of the planets
	std::vector<graph<planet *> *> m_graphs;
};

#endif