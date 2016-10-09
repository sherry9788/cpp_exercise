#ifndef RADIX
#define RADIX

#include <vector>

#include "link.h"
#include "queue.h"

using namespace std;

// loc �ǲ�ͬ�����е�һ��ȡ�ຯ��
inline int loc(int num, int index, int step);

// ��������
void radixsort(vector<int> &vec, int &n_compare, int &n_move, int step = 10);

#endif