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

// ����������
template <typename T>
void quicksort(vector<T> &vec, int &n_compare, int i = 0, int j = INT_MIN) {
	// ��ʼ�� j
	if (j == INT_MIN) {
		j = vec.size() - 1;
	}
	// �������������
	if (j - i < 1)
		return;
	// �Ե�һ��Ԫ��Ϊ��׼
	T tmp = vec[i];
	int x = i, y = j;
	// ������С�� tmp ��Ԫ�طŵ� tmp ��ߣ�����ŵ��ұ�
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
	// �� tmp ��ߵĺ��ұߵ�����ֱ����������������ĵݹ�
	quicksort(vec, n_compare, i, x - 1);
	quicksort(vec, n_compare, x + 1, j);
}

// ����Ŀ������򷨡��Ӵ�С����
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