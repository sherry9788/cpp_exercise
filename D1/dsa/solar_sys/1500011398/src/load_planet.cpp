#include "load_planet.h"

planet *load_planet(std::vector<planet *> &all_planet) {
	
	planet *sun = new planet("sun", 0, 0, 0, r_sun, m_sun);
	
#ifndef USE_HASHTABLE
	sun->add_satellite("mercury", d_mercury, i_mercury, e_mercury, r_mercury, m_mercury);
	sun->add_satellite("venus", d_venus, i_venus, e_venus, r_venus, m_venus);
	sun->add_satellite("earth", d_earth, i_earth, e_earth, r_earth, m_earth);
	sun->add_satellite("mars", d_mars, i_mars, e_mars, r_mars, m_mars);
	sun->add_satellite("jupiter", d_jupiter, i_jupiter, e_jupiter, r_jupiter, m_jupiter);
	sun->add_satellite("saturn", d_saturn, i_saturn, e_saturn, r_saturn, m_saturn);
	sun->add_satellite("uranus", d_uranus, i_uranus, e_uranus, r_uranus, m_uranus);
	sun->add_satellite("neptune", d_neptune, i_neptune, e_neptune, r_neptune, m_neptune);
#else
	sun->add_satellite("earth", d_earth, i_earth, 0, r_earth, m_earth);
#endif

	all_planet.push_back(sun);

	for (auto c : sun->get_satellite())
		all_planet.push_back(c);

	all_planet[3]->add_satellite("moon", d_moon, i_moon, e_moon, r_moon, m_moon);
	all_planet.push_back(all_planet[3]->get_satellite()[0]);

	for (auto c : all_planet)
		c->set_interaction_planet_vector();

	return sun;
}
