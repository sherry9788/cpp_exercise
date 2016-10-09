#include <iostream>
#include <cassert>
#include <random>
#include <ctime>
#include <climits>
#include <vector>
#include <cstdlib>

using namespace std;

template <typename T>
void quicksort(vector<T> &vec, int i = 0, int j = INT_MIN) {
	if (j == INT_MIN) {
		j = vec.size() - 1;
	}
	if (j - i < 1)
		return;
	T tmp = vec[i];
	int x = i, y = j;
	while (true) {
		while (vec[y] >= tmp && x != y)
			--y;
		if (x == y)
			break;
		vec[x] = vec[y];
		while (vec[x] < tmp && x != y)
			++x;
		if (x == y)
			break;
		vec[y] = vec[x];
	}
	vec[x] = tmp;
	quicksort(vec, i, x - 1);
	quicksort(vec, x + 1, j);
}

int main() {
	vector<int> vec;
loop:
	srand(clock());
	vec.erase(vec.begin(), vec.end());
	int n;
	cin >> n;
	for (int i = 0; i < n * 100000; ++i)
		vec.push_back(rand());
	double x = clock();
	quicksort(vec);
	cerr << clock() - x << endl;
	goto loop;
	return 0;
}
