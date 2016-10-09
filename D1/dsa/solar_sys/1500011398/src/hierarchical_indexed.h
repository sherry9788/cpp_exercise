#ifndef INDEXED
#define INDEXED

#include <vector>
#include <iostream>

#include "hashtable.h"

struct hierarchical_index {
	// function
public:
	// enter info
	void enter(const int &index_1, const int &index_2, const int &index_3, 
		const double &value_1, const double &value_2, const double &value_3);
	// get info
	void get_data(const int &index_1, const int &index_2, const int &index_3,
		double &value_1, double &value_2, double &value_3);
	// constructor
	hierarchical_index(int n_size_1, int n_size_2, int n_size_3);
	// destructor
	~hierarchical_index();

	// we don't need the assignment function 
	// and copy constructor

	// data
private:
	// the info
	HashTable<int, HashTable<int, HashTable<int, double *> *> *> *content;
	// the size
	int size_1, size_2, size_3;
};

#endif