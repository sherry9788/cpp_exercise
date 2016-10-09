#ifndef QUICK
#define QUICK

#include <iostream>
#include <cassert>
#include <random>
#include <ctime>
#include <climits>
#include <vector>
#include <cstdlib>

using namespace std;

// 快速排序函数
template <typename T>
void quicksort(vector<T> &vec, int &n_compare, int i = 0, int j = INT_MIN) {
	// 初始化 j
	if (j == INT_MIN) {
		j = vec.size() - 1;
	}
	// 排序结束，返回
	if (j - i < 1)
		return;
	// 以第一个元素为标准
	T tmp = vec[i];
	int x = i, y = j;
	// 把所有小于 tmp 的元素放到 tmp 左边，其余放到右边
	while (true) {
		++n_compare;
		while (vec[y] >= tmp && ++n_compare && x != y)
			--y;
		if (x == y)
			break;
		vec[x] = vec[y];
		while (vec[x] < tmp && ++n_compare && x != y)
			++x;
		if (x == y)
			break;
		vec[y] = vec[x];
	}
	vec[x] = tmp;
	// 对 tmp 左边的和右边的数组分别进行整理，调用自身的递归
	quicksort(vec, n_compare, i, x - 1);
	quicksort(vec, n_compare, x + 1, j);
}

// 反序的快速排序法。从大到小排序
template <typename T>
void r_quicksort(vector<T> &vec, int i = 0, int j = INT_MIN) {
	if (j == INT_MIN) {
		j = vec.size() - 1;
	}
	if (j - i < 1)
		return;
	T tmp = vec[i];
	int x = i, y = j;
	while (true) {
		while (vec[y] <= tmp && x != y)
			--y;
		if (x == y)
			break;
		vec[x] = vec[y];
		while (vec[x] > tmp && x != y)
			++x;
		if (x == y)
			break;
		vec[y] = vec[x];
	}
	vec[x] = tmp;
	r_quicksort(vec, i, x - 1);
	r_quicksort(vec, x + 1, j);
}

#endif