#include <vector>
#include <iostream>
#include <random>

// ����Ԫ��
template <typename T>
inline void swap(T &x, T &y) {
	T tmp = x;
	x = y;
	y = tmp;
}

// ˫���ð������
 template <typename T>
void double_bubble_sort(std::vector<T> &elements) {
	// i ��¼��ǰ���Ԫ�ص������� f ��¼�����Ԫ�ص�����
	int i(0), f(elements.size() - 1);
	while (i != f) {
		// ��������
		for (int index = i; index != f; ++index) {
			if (elements[index] > elements[index + 1])
				swap(elements[index], elements[index + 1]);
		}
		--f;
		if (i == f)
			break;
		// ��������
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