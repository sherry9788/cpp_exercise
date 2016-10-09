#ifndef QUICK
#define QUICK

#include <vector>
#include <climits>

using namespace std;

//quicksort是一个快速排序函数
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

#endif