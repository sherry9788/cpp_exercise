#ifndef MERGE
#define MERGE

#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

// �鲢�������ĵݹ鲿��
template <typename T>
void merge(vector<vector<T> > &vec, int &n_compare, int &n_move) {
	// ���vector��ֻʣһ��Ԫ�أ�˵�������Ѿ�ִ����ϣ�ֱ�ӷ���
	if (vec.size() == 1)
		return;
	// �Ե�ǰ����ִ������
	for (int i = 0; i + 1 < vec.size(); ++i) {
		// �����ڵ���������鲢
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
	// �ݹ�ִ��
	merge(vec, n_compare, n_move);
}

// �鲢������
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