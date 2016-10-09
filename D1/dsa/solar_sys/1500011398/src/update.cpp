#include "update.h"

void planet::update_position_velocity(int step) {
	bool has_calculated_position = false;
#ifdef USE_HASHTABLE
	vector<double> force;
	force.resize(3);
#endif
	for (auto c : interaction_planet) {
		double delta_x = m_x - c->m_x;
		double delta_y = m_y - c->m_y;
		double delta_z = m_z - c->m_z;
#ifndef USE_HASHTABLE
		double Distance = sqrt(delta_x * delta_x +
			delta_y * delta_y + delta_z * delta_z);
		if (!has_calculated_position && Distance * 0.1 < (m_radius + c->m_radius)) {
			has_calculated_position = true;
			// use the judgement of time to avoid the 
			// surplus collisions
			double double_step = step / 50.;
			for (int i = 0; i < 50; ++i) {
				if(i != 0)
					Distance = sqrt(delta_x * delta_x +
						delta_y * delta_y + delta_z * delta_z);

				if (Distance < (m_radius + c->m_radius)
					&& clock() - last_collision_time > 10000) {
					std::cerr << "collision happened" << std::endl;
					collision(this, c);
					last_collision_time = clock();
					c->last_collision_time = clock();
					break;
				}

				double F = c->GM / (Distance * Distance * Distance);
				double a_x = F * delta_x;
				double a_y = F * delta_y;
				double a_z = F * delta_z;
				m_x -= 0.5 * a_x * double_step * double_step;
				m_y -= 0.5 * a_y * double_step * double_step;
				m_z -= 0.5 * a_z * double_step * double_step;
				m_vx -= a_x * double_step;
				m_vy -= a_y * double_step;
				m_vz -= a_z * double_step;
				m_x += m_vx * double_step;
				m_y += m_vy * double_step;
				m_z += m_vz * double_step;
			}
		}
		else if (!has_calculated_position && Distance * 0.02 < (m_radius + c->m_radius)) {
			has_calculated_position = true;
			// use the judgement of time to avoid the 
			// surplus collisions
			double double_step = step / 10.;
			for (int i = 0; i < 10; ++i) {
				if (i != 0)
					Distance = sqrt(delta_x * delta_x +
						delta_y * delta_y + delta_z * delta_z);

				if (Distance < (m_radius + c->m_radius)
					&& clock() - last_collision_time > 10000) {
					std::cerr << "collision happened" << std::endl;
					collision(this, c);
					last_collision_time = clock();
					c->last_collision_time = clock();
					break;
				}

				double F = c->GM / (Distance * Distance * Distance);
				double a_x = F * delta_x;
				double a_y = F * delta_y;
				double a_z = F * delta_z;
				m_x -= 0.5 * a_x * double_step * double_step;
				m_y -= 0.5 * a_y * double_step * double_step;
				m_z -= 0.5 * a_z * double_step * double_step;
				m_vx -= a_x * double_step;
				m_vy -= a_y * double_step;
				m_vz -= a_z * double_step;
				m_x += m_vx * double_step;
				m_y += m_vy * double_step;
				m_z += m_vz * double_step;
			}
		}
		else {
			double F = c->GM / (Distance * Distance * Distance);
			double a_x = F * delta_x;
			double a_y = F * delta_y;
			double a_z = F * delta_z;
			m_x -= 0.5 * a_x * step * step;
			m_y -= 0.5 * a_y * step * step;
			m_z -= 0.5 * a_z * step * step;
			m_vx -= a_x * step;
			m_vy -= a_y * step;
			m_vz -= a_z * step;
		}
#else
		m_parent->get_distance_force_dictionary().get_data(
			(int)(delta_x * 5000),
			(int)(delta_y * 5000),
			(int)(delta_z * 5000),
			force[0],
			force[1],
			force[2]
		);
		m_x += 0.5 * force[0] * step * step;
		m_y += 0.5 * force[1] * step * step;
		m_z += 0.5 * force[2] * step * step;
		m_vx += force[0] * step;
		m_vx += force[1] * step;
		m_vx += force[2] * step;
#endif
	}

	for (auto c : interaction_planet_of_the_same_layer) {
		double delta_x = m_x - c->m_x;
		double delta_y = m_y - c->m_y;
		double delta_z = m_z - c->m_z;
#ifndef USE_HASHTABLE
		double Distance = sqrt(delta_x * delta_x +
			delta_y * delta_y + delta_z * delta_z);
		if (!has_calculated_position && Distance * 0.1 < (m_radius + c->m_radius)) {
			has_calculated_position = true;
			// use the judgement of time to avoid the 
			// surplus collisions
			double double_step = step / 50.;
			for (int i = 0; i < 50; ++i) {
				if (i != 0)
					Distance = sqrt(delta_x * delta_x +
						delta_y * delta_y + delta_z * delta_z);

				if (Distance < (m_radius + c->m_radius)
					&& clock() - last_collision_time > 10000) {
					std::cerr << "collision happened" << std::endl;
					collision(this, c);
					last_collision_time = clock();
					c->last_collision_time = clock();
					break;
				}

				double F = c->GM / (Distance * Distance * Distance);
				double a_x = F * delta_x;
				double a_y = F * delta_y;
				double a_z = F * delta_z;
				m_x -= 0.5 * a_x * double_step * double_step;
				m_y -= 0.5 * a_y * double_step * double_step;
				m_z -= 0.5 * a_z * double_step * double_step;
				m_vx -= a_x * double_step;
				m_vy -= a_y * double_step;
				m_vz -= a_z * double_step;
				m_x += m_vx * double_step;
				m_y += m_vy * double_step;
				m_z += m_vz * double_step;
			}
		}
		else if (!has_calculated_position && Distance * 0.02 < (m_radius + c->m_radius)) {
			has_calculated_position = true;
			// use the judgement of time to avoid the 
			// surplus collisions
			double double_step = step / 10.;
			for (int i = 0; i < 10; ++i) {
				if (i != 0)
					Distance = sqrt(delta_x * delta_x +
						delta_y * delta_y + delta_z * delta_z);

				if (Distance < (m_radius + c->m_radius)
					&& clock() - last_collision_time > 10000) {
					std::cerr << "collision happened" << std::endl;
					collision(this, c);
					last_collision_time = clock();
					c->last_collision_time = clock();
					break;
				}

				double F = c->GM / (Distance * Distance * Distance);
				double a_x = F * delta_x;
				double a_y = F * delta_y;
				double a_z = F * delta_z;
				m_x -= 0.5 * a_x * double_step * double_step;
				m_y -= 0.5 * a_y * double_step * double_step;
				m_z -= 0.5 * a_z * double_step * double_step;
				m_vx -= a_x * double_step;
				m_vy -= a_y * double_step;
				m_vz -= a_z * double_step;
				m_x += m_vx * double_step;
				m_y += m_vy * double_step;
				m_z += m_vz * double_step;
			}
		}
		else {
			double F = c->GM / (Distance * Distance * Distance);
			double a_x = F * delta_x;
			double a_y = F * delta_y;
			double a_z = F * delta_z;
			m_x -= 0.5 * a_x * step * step;
			m_y -= 0.5 * a_y * step * step;
			m_z -= 0.5 * a_z * step * step;
			m_vx -= a_x * step;
			m_vy -= a_y * step;
			m_vz -= a_z * step;
		}
#else
		m_parent->get_distance_force_dictionary().get_data(
			(int)(delta_x * 5000),
			(int)(delta_y * 5000),
			(int)(delta_z * 5000),
			force[0],
			force[1],
			force[2]
		);
		m_x += 0.5 * force[0] * step * step;
		m_y += 0.5 * force[1] * step * step;
		m_z += 0.5 * force[2] * step * step;
		m_vx += force[0] * step;
		m_vx += force[1] * step;
		m_vx += force[2] * step;
#endif
	}
	if (!has_calculated_position) {
		m_x += m_vx * step;
		m_y += m_vy * step;
		m_z += m_vz * step;
	}
#ifdef COEFFICIENT_VISCOSITY
	m_vx -= m_vx * COEFFICIENT_VISCOSITY * step;
	m_vy -= m_vy * COEFFICIENT_VISCOSITY * step;
	m_vz -= m_vz * COEFFICIENT_VISCOSITY * step;
#endif
}

updater::updater(const std::vector<planet *> &all_planet) {
	planets = all_planet;
	counter = 0;
	planets_by_layer.resize(3);
	for (auto c : all_planet) {
		planets_by_layer[c->get_layer()].push_back(c);
	}
	for (int i = 0; i < 3; ++i) {
		m_graphs.push_back(new graph<planet *>(planets_by_layer[i]));
	}
	m_graphs[0]->threshold = THRESHOLD_0;
	m_graphs[1]->threshold = THRESHOLD_1;
	m_graphs[2]->threshold = THRESHOLD_2;
	update_graphs();
}

void updater::work(const int step, const int period) {
	int Max_index = period / step;
	for (int index = 0; index < Max_index; ++index) {
		for (auto c : planets)
			c->update_position_velocity(step);
	}
	if ((++counter) % PERIOD_FRESH_GRAPH == 0) {
		update_graphs();
	}
}

void updater::add_planet(planet *new_planet) {
	planets.push_back(new_planet);
	planets_by_layer[new_planet->get_layer()].push_back(new_planet);
	m_graphs[new_planet->get_layer()]->add_vertex(new_planet);
	update_graphs();
}

void updater::update_graphs() {
	for (int i = 0; i < m_graphs.size(); ++i) {
		for (int j = 1; j < m_graphs[i]->size(); ++j) {
			for (int k = 0; k < j; ++k) {
				double delta_x =
					m_graphs[i]->vertex()[j]->m_x
					- m_graphs[i]->vertex()[k]->m_x;
				double delta_y =
					m_graphs[i]->vertex()[j]->m_y
					- m_graphs[i]->vertex()[k]->m_y;
				double delta_z =
					m_graphs[i]->vertex()[j]->m_z
					- m_graphs[i]->vertex()[k]->m_z;
				double Distance = sqrt(delta_x * delta_x
					+ delta_y * delta_y + delta_z * delta_z);
				m_graphs[i]->get_sides(k, j) = Distance;
			}
		}
	}

	for (auto c : planets) {
		c->get_interaction_planet_of_the_same_layer().clear();
	}

	for (int i = 0; i < m_graphs.size(); ++i) {
		for (int j = 0; j < m_graphs[i]->size(); ++j) {
			for (int k = 0; k < m_graphs[i]->size(); ++k) {
				if (k != j && m_graphs[i]->vertex()[k]->GM
					/ m_graphs[i]->get_sides(k, j)
					/ m_graphs[i]->get_sides(k, j) >
					m_graphs[i]->threshold) {
					m_graphs[i]->vertex()[j]->
						get_interaction_planet_of_the_same_layer().
						push_back(m_graphs[i]->vertex()[k]);
				}
			}
		}
	}
}