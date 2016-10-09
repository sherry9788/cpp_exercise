#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <iostream>
#include <cassert>
#include <random>
#include <ctime>
#include <climits>
#include <cstdlib>

using namespace std;

// ����Ϊ 2 ���ݺ���
int power2(int n);

// ���ȶ�����
template <typename T>
struct priorityQueue {
	//data
	// ����
	T *data;
	// ���ݸ���
	int n;
	// ����
	int max;

	//function
	// constructor
	priorityQueue<T>(int n_max = INT_MAX);

	// destructor
	~priorityQueue<T>();

	// assignment function
	priorityQueue<T> &operator=(const priorityQueue<T> &p);

	// copy constructor
	priorityQueue<T>(const priorityQueue<T> &p);

	// ��λ��ĳһ��Ԫ��
	T &operator[](int num);

	// ��ӡ����Ԫ��
	priorityQueue &print();

	// ���һ��Ԫ�أ���¼�Ƚϴ���
	void add(T x, int &n_compare);

	// ����СԪ�س��ӣ�ͬʱ���ظ�Ԫ�ص�ֵ����¼�Ƚϴ���
	T removeMin(int &n_compare);
};

template <typename T>
priorityQueue<T>::priorityQueue(int n_max = INT_MAX) {
	max = n_max;
	data = new T[max];
	assert(data);
	n = 0;
}

template <typename T>
priorityQueue<T>::~priorityQueue() {
	if (data)
		delete[]data;
}

template <typename T>
priorityQueue<T> &priorityQueue<T>::operator=(const priorityQueue<T> &p) {
	if (data)
		delete[]data;
	max = p.max;
	data = new T[max];
	assert(data);
	n = p.n;
	for (int i = 0; i < n; ++i) {
		data[i] = p.data[i];
	}
}

template <typename T>
priorityQueue<T>::priorityQueue(const priorityQueue &p) {
	max = p.max;
	n = p.n;
	data = new T[max];
	assert(data);
	for (int i = 0; i < n; ++i) {
		data[i] = p.data[i];
	}
}

template <typename T>
T &priorityQueue<T>::operator[](int num) {
	assert(num < n);
	return data[num];
}

template <typename T>
priorityQueue<T> &priorityQueue<T>::print()
{
	for (int layer = 1; power2(layer - 1) <= n; ++layer)
	{
		for (int i = power2(layer - 1) - 1; (i < power2(layer) - 1)
			&& i < n; ++i)
			cerr << data[i] << " ";

		cerr << endl;
	}
	return *this;
}

template <typename T>
void priorityQueue<T>::add(T x, int &n_compare) {
	assert(n < max);
	int pos = n;
	while (pos > 0 && data[(pos - 1) / 2] > x) {
		++n_compare;
		data[pos] = data[(pos - 1) / 2];
		pos = (pos - 1) / 2;
	}
	++n;
	data[pos] = x;
}

template <typename T>
T priorityQueue<T>::removeMin(int &n_compare)
{
	assert(n > 0);
	T ret = data[0];
	int i;
	for (i = 0; i * 2 + 2 < n;)
	{
		if (data[i * 2 + 1] < data[i * 2 + 2])
		{
			++n_compare;
			data[i] = data[i * 2 + 1];
			i = i * 2 + 1;
		}
		else
		{
			data[i] = data[i * 2 + 2];
			i = i * 2 + 2;
		}
	}

	data[i] = data[n - 1];
	if (i * 2 + 2 != n && data[i] < data[(i - 1) / 2])
	{
		++n_compare;
		T temp = data[i];
		data[i] = data[(i - 1) / 2];
		data[(i - 1) / 2] = temp;
	}
	--n;
	return ret;
}

#endif