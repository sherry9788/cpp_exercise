#ifndef MERGE
#define MERGE

#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

// 归并排序函数的递归部分
template <typename T>
void merge(vector<vector<T> > &vec, int &n_compare, int &n_move) {
	// 如果vector中只剩一个元素，说明排序已经执行完毕，直接返回
	if (vec.size() == 1)
		return;
	// 对当前数组执行搜索
	for (int i = 0; i + 1 < vec.size(); ++i) {
		// 把相邻的两个数组归并
		auto iter_1 = vec.begin() + i;
		auto iter_2 = vec.begin() + i + 1;
		auto iter_3 = iter_1->begin();
		auto iter_4 = iter_2->begin();
		vector<T> tmp;
		while (iter_3 != iter_1->end() && iter_4 != iter_2->end()) {
			++n_compare;
			if (*iter_3 < *iter_4) {
				++n_move;
				tmp.push_back(*iter_3);
				++iter_3;
			}
			else {
				++n_move;
				tmp.push_back(*iter_4);
				++iter_4;
			}
		}
		while (iter_3 != iter_1->end()) {
			++n_move;
			tmp.push_back(*iter_3);
			++iter_3;
		}
		while (iter_4 != iter_2->end()) {
			++n_move;
			tmp.push_back(*iter_4);
			++iter_4;
		}
		*iter_1 = tmp;
		vec.erase(iter_2);
	}
	// 递归执行
	merge(vec, n_compare, n_move);
}

// 归并排序函数
template <typename T>
void mergeSort(vector<T> &vec, int &n_compare, int &n_move) {
	n_move = 0;
	vector<vector<T> > tmp;
	for (auto c : vec)
		tmp.push_back(vector<T>{c});
	merge(tmp, n_compare, n_move);
	int i = 0;
	vec = tmp[0];
}

#endif