#include <iostream>
#include <cassert>
#include <random>
#include <ctime>
#include <climits>
#include <cstdlib>

using namespace std;

int power2(int n)
{
	if (n == 0)
		return 1;
	else
		return 2 * power2(n - 1);
}

template <typename T>
struct priorityQueue {
	//data
	T *data;
	int n;
	int max;

	//function
	priorityQueue<T>(int n_max = INT_MAX) {
		max = n_max;
		data = new T[max];
		assert(data);
		n = 0;
	}

	~priorityQueue<T>() {
		if (data)
			delete[]data;
	}

	priorityQueue<T> &operator=(const priorityQueue<T> &p) {
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

	priorityQueue<T>(const priorityQueue<T> &p) {
		max = p.max;
		n = p.n;
		data = new T[max];
		assert(data);
		for (int i = 0; i < n; ++i) {
			data[i] = p.data[i];
		}
	}

	T &operator[](int num) {
		assert(num < n);
		return data[num];
	}

	priorityQueue &print()
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

	void add(T x) {
		assert(n < max);
		int pos = n;
		while (pos > 0 && data[(pos - 1) / 2] > x) {
			data[pos] = data[(pos - 1) / 2];
			pos = (pos - 1) / 2;
		}
		++n;
		data[pos] = x;
	}

	T removeMin()
	{
		assert(n > 0);
		T ret = data[0];
		int i;
		for (i = 0; i * 2 + 2 < n;)
		{
			if (data[i * 2 + 1] < data[i * 2 + 2])
			{
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
			T temp = data[i];
			data[i] = data[(i - 1) / 2];
			data[(i - 1) / 2] = temp;
		}
		--n;
		return ret;
	}
};

template <typename K, typename V>
struct element {
	//data
	K key;
	V value;
	element<K, V> *next = nullptr;

	//function
	element<K, V>() = default;
	element<K, V>(K n_key, element<K, V> *n_next = nullptr, V n_value = V()) :
		key(n_key), next(n_next), value(n_value) {}

	~element() {
		if (next)
			delete next;
	}

	element<K, V> &operator=(element<K, V> &E) {
		key = E.key;
		value = E.value;
		if (E.next)
			next = new element<K, V>();
		*next = *E.next;
	}

	element<K, V>(element<K, V> &E) {
		key = E.key;
		value = E.value;
		if (E.next)
			next = new element<K, V>(*E.next);
	}

	element<K, V> &operator[](int n) {
		if (n == 0)
			return *this;
		else
			return (*next)[n - 1];
	}

	int operator-(const element<K, V> &e) {
		if (&e == this)
			return 0;
		auto ptr = &e;

		int n = 1;
		while (ptr) {
			ptr = ptr->next;
			if (ptr == this)
				return n;
			++n;
		}
		assert(false);
		return -1;
	}

	bool add(K n_key) {
		auto tmp = this;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new element<K, V>(n_key);
		if (tmp->next)
			return true;
		return false;
	}

	void print() {
		auto tmp = this;
		while (tmp) {
			cerr << tmp->key << " ";
			tmp = tmp->next;
		}
		cerr << endl;
	}

	void swap(element<K, V> *ptr) {
		if (this == ptr)
			return;
		K tmp_k = key;
		V tmp_value = value;
		key = ptr->key;
		value = ptr->value;
		ptr->key = tmp_k;
		ptr->value = tmp_value;
	}

	void selectSort() {
		auto tmp = this;
		while (tmp) {
			auto curr = tmp->next, min = tmp;
			while (curr) {
				if (curr->key < min->key)
					min = curr;
				curr = curr->next;
			}
			tmp->swap(min);
			tmp = tmp->next;
		}
	}

	void heapSort() {
		auto tmp = this;
		priorityQueue<K> p(1000000);
		while (tmp) {
			p.add(tmp->key);
			tmp = tmp->next;
		}
		tmp = this;
		while (p.n != 0) {
			tmp->key = p.removeMin();
			tmp = tmp->next;
		}
	}
};

template <typename K, typename V>
ostream &operator<<(ostream &out, const element<K, V> &E) {
	out << E.key;
	return out;
}

int main() {
	element<int, int> e(0);
	int n;
loop:
	cin >> n;
	for (int i = 0; i < n; ++i) {
		e.add(rand());
	}
	e.heapSort();
	e.print();
	goto loop;
	return 0;
}
