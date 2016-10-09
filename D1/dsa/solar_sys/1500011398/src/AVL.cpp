#include "AVL.h"

int cal_r(std::map<std::vector<int>, int> &C, int i, int j, int &r) {
	int ret;
	assert(j >= i);
	int curr = INT_MAX;
	for (ret = i + 1; ret <= j; ++ret) {
		if (C[std::vector<int>{ i, ret - 1 }] + C[std::vector<int>{ ret, j }] < curr) {
			curr = C[std::vector<int>{ i, ret - 1 }] + C[std::vector<int>{ ret, j }];
			r = ret;
		}
	}
	return curr;
}