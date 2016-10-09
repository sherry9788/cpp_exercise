#ifndef BUCKET
#define BUCKET

#include <cstdlib>
#include <strstream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

// a bucket structure
struct bucket {
public:
	// function
	// enter info
	void enter(const int &index_1, const int &index_2, const int &index_3,
		const double &value_1, const double &value_2, const double &value_3);
	// get info
	void get_data(const int &index_1, const int &index_2, const int &index_3,
		double &value_1, double &value_2, double &value_3);
	// constructor
	bucket();

private:
	// data
	// nothing here
};

#endif