#include "Header.h"

template <class T>
void print(T x) {
	T y = x;
	std::cerr << y << std::endl;
}

int main() {
	int x = 1;
	print(x);
	return 0;
}