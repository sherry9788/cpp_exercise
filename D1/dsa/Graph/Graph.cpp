#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

using T = int;

struct vertex {
	//data
	T info;
	vector<vertex *> out;
	vector<vertex *> in;
	bool mark = false;

	//function
	vertex() = default;
	vertex(T n_info) :
		info(n_info) {}
};

struct stack {
	//data
	vector<vertex *> data;
	vertex *info = nullptr;

	//function
	stack() = default;

	void push(vertex *n_info) {
		data.push_back(n_info);
		info = n_info;
	}

	vertex *pop() {
		auto tmp = info;
		data.erase(data.end() - 1);
		if (!data.empty())
			info = data[data.size() - 1];
		else
			info = nullptr;
		return tmp;
	}

	bool isEmpty() {
		return data.size() == 0;
	}
};

struct queue {
	//data
	vector<vertex *> data;

	//function
	queue() = default;

	void enter(vertex *n_info) {
		data.push_back(n_info);
	}

	vertex *kick() {
		auto tmp = data[data.size() - 1];
		data.erase(data.end() - 1);
		return tmp;
	}

	bool isEmpty() {
		return data.size() == 0;
	}
};

struct graph {
	//data
	vector<vertex *> V;

	//function
	graph() = default;
	graph(const vector<T> &info, const vector<vector<bool> > &adj) {
		for (auto c : info)
			V.push_back(new vertex(c));
		for (unsigned i = 0; i < adj.size(); ++i)
			for (unsigned j = 0; j < adj.size(); ++j)
				if (adj[i][j]) {
					V[i]->out.push_back(V[j]);
					V[j]->in.push_back(V[i]);
				}
	};

	~graph() {
		for (auto c : V)
			delete c;
	}

	void restore() {
		for (auto c : V)
			c->mark = false;
	}

	void dft() {
		stack s;
		s.push(V[0]);
		V[0]->mark = true;
		while (!s.isEmpty()) {
			vertex *tmp = s.pop();
			cerr << tmp->info << ' ';
			for (int i = tmp->out.size() - 1; i >= 0; --i) {
				if (!tmp->out[i]->mark)
					s.push(tmp->out[i]);
				tmp->out[i]->mark = true;
			}
		}
		cerr << endl;
		restore();
	}

	void bft() {
		queue q;
		q.enter(V[0]);
		V[0]->mark = true;
		while (!q.isEmpty()) {
			auto tmp = q.kick();
			cerr << tmp->info << ' ';
			for (auto c : tmp->out) {
				if (!c->mark)
					q.enter(c);
				c->mark = true;
			}
		}
		cerr << endl;
		restore();
	}
};

using namespace std;

int main() {
	vector<int> v{ 1, 2, 3, 4, 5 };
	vector<vector<bool> > adj{
		{ 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 1, 1 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	};
	graph g(v, adj);
	g.bft();
	g.dft();
	return 0;
}
