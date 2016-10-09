#ifndef GRAPH
#define GRAPH

#include <vector>

class updater;

template <typename T>
class graph {
	friend class updater;
	// function
public:
	// constructor
	graph(std::vector<T> n_vertex = std::vector<T>()) {
		m_vertex = n_vertex;
		m_sides.resize(n_vertex.size());
		for (int i = 0; i < m_vertex.size(); ++i) {
			m_sides[i].resize(n_vertex.size());
		}
	}

	// add a vertex
	void add_vertex(T new_element) {
		m_vertex.push_back(new_element);
		m_sides.resize(m_vertex.size());
		for (int i = 0; i < m_vertex.size(); ++i) {
			m_sides[i].resize(m_vertex.size());
		}
	}

	// this function can return the infomation of the sides
	double &get_sides(int x, int y) {
		if (x < y) {
			int tmp = x;
			x = y;
			y = tmp;
		}
		return m_sides[x][y];
	}

	int size() {
		return m_vertex.size();
	}

	std::vector<T> &vertex() {
		return m_vertex;
	}

	//data
private:
	std::vector<T> m_vertex;
	std::vector<std::vector<double> > m_sides;
	double threshold = 0;
};

#endif