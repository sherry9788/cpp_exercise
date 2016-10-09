#include "radix_sort.h"

inline int loc(int num, int index, int step = 10) {
	if (index == 1)
		return num % step;
	else
		return loc(num / step, index - 1, step);
}

void radixsort(vector<int> &vec, int &n_compare, int step) {
	int n = 0;
	// Ѱ������Ԫ��
	for (auto c : vec)
		if (c > n)
			n = c;
	int num = 1, index_max = 2;
	// �������Ԫ�ص�λ��
	while (n > num * step - 1) {
		num *= step;
		++index_max;
	}
	n_compare = index_max * step;

	//����һ�����е�����
	queue<int> *q = new queue<int>[step];

	// ִ��������
	for (int index = 1; index < index_max; ++index) {
		// �ӵ�λ��ʼִ��
		// �ռ�����
		for (auto c : vec)
			q[loc(c, index, step)].Enter(c);
		int k = 0;
		// �������
		for (int i = 0; i < step; ++i)
			while (!q[i].isEmpty())
				vec[k++] = q[i].Kick();
	}
	delete[]q;
}