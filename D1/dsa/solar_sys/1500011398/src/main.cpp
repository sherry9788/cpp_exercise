#include "load_planet.h"
#include "display.h"
#include "hierarchical_indexed.h"
#include "bucket.h"

int main() {
	// create a vector to store the planets
	std::vector<planet *> all_planet;
	// load the planets
	load_planet(all_planet);

	// display them
	display(all_planet);
	
	return 0;
}