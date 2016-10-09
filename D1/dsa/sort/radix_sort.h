#ifndef RADIX
#define RADIX

#include <vector>

#include "link.h"
#include "queue.h"

using namespace std;

// loc 是不同进制中的一个取余函数
inline int loc(int num, int index, int step);

// 基数排序法
void radixsort(vector<int> &vec, int &n_compare, int &n_move, int step = 10);

#endif