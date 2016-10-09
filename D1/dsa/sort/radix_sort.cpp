#include "radix_sort.h"

inline int loc(int num, int index, int step = 10) {
	if (index == 1)
		return num % step;
	else
		return loc(num / step, index - 1, step);
}

void radixsort(vector<int> &vec, int &n_compare, int &n_move, int step) {
	n_move = 0;
	int n = 0;
	// 寻找最大的元素
	for (auto c : vec)
		if (c > n)
			n = c;
	int num = 1, index_max = 2;
	// 计算最大元素的位数
	while (n > num * step - 1) {
		num *= step;
		++index_max;
	}
	n_compare = index_max * step;

	//创建一个队列的数组
	queue<int> *q = new queue<int>[step];

	// 执行主函数
	for (int index = 1; index < index_max; ++index) {
		// 从地位开始执行
		// 收集过程
		n_move += 2 * vec.size();
		for (auto c : vec)
			q[loc(c, index, step)].Enter(c);
		int k = 0;
		// 分配过程
		for (int i = 0; i < step; ++i)
			while (!q[i].isEmpty())
				vec[k++] = q[i].Kick();
	}
	delete[]q;
}