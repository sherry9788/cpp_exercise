#include "planet.h"

planet::planet(std::string n_name, double n_d, double n_inclination,
	double n_e, double n_radius, double n_mass, planet *n_parent)
{
	GM = G * n_mass;
	m_parent = n_parent;
	m_name = n_name;
	m_mass = n_mass;
	// and sun and that of the moon and earth
	m_radius = n_radius / 23374.6671875;
	// using float cuz OpenGL only accept float value
	display_radius = (float)m_radius;
	// if n_e == 1, the orbit is parabola
	if (n_e >= 1) {
		double total_velocity = 0.517638 * sqrt(m_parent->GM / n_d);
		m_x = n_d * 3.732050808;
		m_y = n_d * 6.464101615 * cos(n_inclination * PI / 180.);
		m_z = n_d * 6.464101615 * sin(n_inclination * PI / 180.);

		m_vx = total_velocity * (-0.2588190451);
		m_vy = total_velocity * (-0.9659258263) * cos(n_inclination * PI / 180.);
		m_vz = total_velocity * (-0.9659258263) * sin(n_inclination * PI / 180.);

		return;
	}

	if (n_parent) {
		// it is a satellite or a planet
		m_y = m_parent->m_y;
		m_x = cos(n_inclination * PI / 180.) * n_d * (1 + n_e) + m_parent->m_x;
		m_z = sin(n_inclination * PI / 180.) * n_d * (1 + n_e) + m_parent->m_z;
		m_vy = sqrt((1 - n_e) / (1 + n_e)*n_parent->GM / n_d) + m_parent->m_vy;
		m_vx = m_parent->m_vx;
		m_vz = m_parent->m_vz;
	} else {
		// it must be the sun
		m_x = 0;
		m_y = 0;
		m_z = 0;
		m_vx = 0;
		m_vy = 0;
		m_vz = 0;
	}

#ifdef USE_HASHTABLE
	if (m_name == "sun")
		calculate_dictionary();
#endif
}

planet::~planet() {
	if (m_angular_momentum)
		delete []m_angular_momentum;
#ifdef USE_HASHTABLE
	if (distance_force_dictionary)
		delete distance_force_dictionary;
#endif
}

double planet::energy() {
	return m_vx * m_vx + m_vy * m_vy + m_vy * m_vy +
		2 * GM / (sqrt(m_x * m_x + m_y * m_y + m_z * m_z));
}

double *planet::angular_momentum() {
	double *ret_angular_momentum = new double[3];
	ret_angular_momentum[0] = m_y * m_vz - m_z * m_vy;
	ret_angular_momentum[1] = m_z * m_vx - m_x * m_vz;
	ret_angular_momentum[2] = m_x * m_vy - m_y * m_vx;
	return ret_angular_momentum;
}

std::ostream &planet::printcoor(std::ostream &out, 
	int n_day, bool whether_display_x, 
	bool whether_display_y, bool whether_display_z,
	bool whether_display_d ){
	
	out << n_day << '\t';
	if (whether_display_x)
		out << m_x << '\t';
	if (whether_display_y)
		out << m_y << '\t';
	if (whether_display_z)
		out << m_z << '\t';
	if (whether_display_d)
		out << sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	return out;
}

planet *planet::add_satellite(planet *p_satellite) {
	satellite.push_back(p_satellite);
	p_satellite->m_parent = this;
	update_layer();
	return p_satellite;
}

planet *planet::add_satellite(std::string n_name, double n_d, double n_inclination,
	double n_e, double n_radius, double n_mass) {
	planet *new_satellite = new planet(n_name, n_d, n_inclination, n_e, n_radius, n_mass, this);
	satellite.push_back(new_satellite);
	update_layer();
	return new_satellite;
}

std::vector<planet *> &planet::get_satellite() {
	return satellite;
}

void planet::update_layer() {
	if (m_parent)
		layer = m_parent->layer + 1;
	for (auto c : satellite)
		c->update_layer();
}

std::vector<planet *> &planet::set_interaction_planet_vector() {
	planet *p_planet = this;
	while (p_planet->m_parent != nullptr)
		p_planet = p_planet->m_parent;
	// use a queue to calculate all the planets that need to
	// be counted on
	queue<planet *> queue_planet(64);
	queue_planet.Enter(p_planet);
	while (!queue_planet.isEmpty()) {
		p_planet = queue_planet.info();
		queue_planet.Kick();
		if (p_planet != this)
			interaction_planet.push_back(p_planet);
		// only the planets whose layer is less
		// with the current planet would be counted on
		if (p_planet->layer < layer - 1)
			for (auto c : p_planet->satellite)
				queue_planet.Enter(c);
	}
	return interaction_planet;
}

std::vector<planet *> &planet::get_interaction_planet() {
	return interaction_planet;
}

std::vector<planet *> &planet::get_interaction_planet_of_the_same_layer() {
	return interaction_planet_of_the_same_layer;
}

int &planet::get_layer() {
	return layer;
}

std::string &planet::get_name() {
	return m_name;
}

float planet::get_x() {
	return (float)m_x;
}

float planet::get_y() {
	return (float)m_y;
}

float planet::get_z() {
	return (float)m_z;
}

float &planet::get_radius() {
	return display_radius;
}

double &planet::get_GM() {
	return GM;
}

void collision(planet *p1, planet *p2) {
	double delta_x = p1->get_x() - p2->get_x();
	double delta_y = p1->get_y() - p2->get_y();
	double delta_z = p1->get_z() - p2->get_z();
	double distance = sqrt(delta_x * delta_x + delta_y
		* delta_y + delta_z * delta_z);
	double cosine_x = delta_x / distance;
	double cosine_y = delta_y / distance;
	double cosine_z = delta_z / distance;
	
	double previous_normal_velocity_1(p1->m_vx * cosine_x +
		p1->m_vy * cosine_y + p1->m_vz * cosine_z);
	double previous_normal_velocity_2(p2->m_vx * cosine_x +
		p2->m_vy * cosine_y + p2->m_vz * cosine_z);

	double later_normal_velocity_1(((p1->m_mass - p2->m_mass) * 
		previous_normal_velocity_1 + 2 * p2->m_mass * previous_normal_velocity_2)
		/ (p1->m_mass + p2->m_mass));

	double later_normal_velocity_2(((p2->m_mass - p1->m_mass) *
		previous_normal_velocity_2 + 1 * p1->m_mass * previous_normal_velocity_1)
		/ (p2->m_mass + p1->m_mass));

	p1->m_vx += (later_normal_velocity_1 - previous_normal_velocity_1) * cosine_x;
	p1->m_vy += (later_normal_velocity_1 - previous_normal_velocity_1) * cosine_y;
	p1->m_vz += (later_normal_velocity_1 - previous_normal_velocity_1) * cosine_z;

	p2->m_vx += (later_normal_velocity_2 - previous_normal_velocity_2) * cosine_x;
	p2->m_vy += (later_normal_velocity_2 - previous_normal_velocity_2) * cosine_y;
	p2->m_vz += (later_normal_velocity_2 - previous_normal_velocity_2) * cosine_z;
}

#ifdef USE_HASHTABLE
void planet::calculate_dictionary() {
	distance_force_dictionary = new 
		hierarchical_index(22000, 22000, 2);
	assert(distance_force_dictionary);
	for (double x = -1.1; x < 1.1; x += 10e-4) {
		for (double y = -1.1; y < 1.1; y += 10e-4) {
			for (double z = 0; z == 0; z += 5e-4) {
				double Distance = -sqrt(x * x + y * y + z * z);
				if (Distance < -0.9 && Distance > -1.1) {
					double Force = GM / Distance / Distance / Distance;
					distance_force_dictionary->enter(
						(int)(x * 5000.),
						(int)(y * 5000.),
						(int)(z * 5000.),
						Force * x,
						Force * y,
						Force * z
					);
				}
			} // for z
		} // for y
	} // for x
}

hierarchical_index &
planet::get_distance_force_dictionary() const{
	return *distance_force_dictionary;
}
#endif