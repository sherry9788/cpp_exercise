#include <vector>
#include <iostream>
#include <random>

// 交换元素
template <typename T>
inline void swap(T &x, T &y) {
	T tmp = x;
	x = y;
	y = tmp;
}

// 双向的冒泡排序
 template <typename T>
void double_bubble_sort(std::vector<T> &elements) {
	// i 记录最前面的元素的序数， f 记录最后面元素的序数
	int i(0), f(elements.size() - 1);
	while (i != f) {
		// 正向搜索
		for (int index = i; index != f; ++index) {
			if (elements[index] > elements[index + 1])
				swap(elements[index], elements[index + 1]);
		}
		--f;
		if (i == f)
			break;
		// 逆向搜索
		for (int index = f; index != i; --index) {
			if (elements[index] < elements[index - 1])
				swap(elements[index], elements[index - 1]);
		}
		++i;
	}
}

int main() {
	std::vector<int> ivec;
	int seed;
	int n;
	std::cin >> seed >> n;
	srand(seed);
	for (int i = 0; i != n; ++i) {
		ivec.push_back(rand());
	}
	double_bubble_sort(ivec);
	for (auto c : ivec)
		std::cerr << c << std::endl;
	return 0;
}