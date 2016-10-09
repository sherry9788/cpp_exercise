#ifndef ELEMENT
#define ELEMENT

#include <iostream>
#include <cassert>
#include <random>
#include <ctime>

#include "priority_queue.h"

using namespace std;

// element ��һ��ģ���࣬�����������
template <typename K, typename V>
struct element {
	// data
	// �ؼ���
	K key;
	// ֵ
	V value;
	// ָ����һ��Ԫ�ص�ָ��
	element<K, V> *next = nullptr;
	// ָʾ�Ƿ�����
	bool isDel = false;

	//function
	// default constructor
	element<K, V>() = default;

	// constructor
	element<K, V>(K n_key, element<K, V> *n_next = nullptr, V n_value = V()) :
		key(n_key), next(n_next), value(n_value) {}

	// destructor
	~element();

	// assignment function
	element<K, V> &operator=(element<K, V> &E);

	// ������ָ��� [] ���������Զ�λ��֮���ĳ������
	element<K, V> &operator[](int n);

	// ������������֮��ľ���
	int operator-(const element<K, V> &e);

	// copy constructor
	element<K, V>(element<K, V> &E);

	// ���һ��Ԫ�ص������ĩβ
	bool add(K n_key, V n_value = V());

	// ��������Ԫ��
	void swap(element<K, V> *ptr);

	// ð������n_compare ��¼�Ƚϴ���
	void bubbleSort(int &n_compare, int &n_move);

	// ��������n_compare ��¼�Ƚϴ���
	void insertsort(int &n_compare, int &n_move);

	// ѡ������n_compare ��¼�Ƚϴ���
	void select_sort(int &n_compare, int &n_move);

	// ������n_compare ��¼�Ƚϴ���
	void heap_sort(int &n_compare, int &n_move);

	// ��ӡ�����е�����Ԫ��
	void print();
};

template <typename K, typename V>
element<K, V> &element<K, V>::operator[](int n) {
	auto ptr_element = this;
	while (n-- > 0) {
		ptr_element = ptr_element->next;
	}
	return *ptr_element;
}

template <typename K, typename V>
element<K, V>::element(element<K, V> &E) {
	key = E.key;
	value = E.value;
	auto ptr_element = E.next;
	auto new_element = this;
	while (ptr_element) {
		new_element->next = new element<K, V>(ptr_element->key, 
			nullptr, ptr_element->value);
		new_element = new_element->next;
		ptr_element = ptr_element->next;
	}
}

template <typename K, typename V>
element<K, V> &element<K, V>::operator=(element<K, V> &E) {
	key = E.key;
	value = E.value;
	if (E.next)
		next = new element<K, V>();
	*next = *E.next;
}

template <typename K, typename V>
element<K, V>::~element() {
	if (isDel)
		return;
	vector<element<K, V> *> del_vec;
	auto ptr = next;
	while (ptr) {
		ptr->isDel = true;
		del_vec.push_back(ptr);
		ptr = ptr->next;
	}

	for (auto c : del_vec)
		delete c;
}

template <typename K, typename V>
bool element<K, V>::add(K n_key, V n_value = V()) {
	auto tmp = this;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new element<K, V>(n_key, nullptr, n_value);
	if (tmp->next)
		return true;
	return false;
}

template <typename K, typename V>
void element<K, V>::bubbleSort(int &n_compare, int &n_move) {
	n_move = 0;
	n_compare = 0;
	auto ptr = this;
	// b ������¼�Ƿ��Ѿ�����
	bool b = false;
	// n ��¼Ԫ�صĸ���
	int n = -1;
	// ͳ��Ԫ�ظ���
	while (ptr) {
		++n;
		ptr = ptr->next;
	}
	for (int i = n; i > 0; --i) {
		ptr = this;
		b = false;
		// ��ǰi��Ԫ�ؽ���һ����������
		// ����ÿ�������ڵ�Ԫ�ؽ���һ������
		while (ptr != &(*this)[i]) {
			++n_compare;
			// �������Ԫ��˳���ˣ�����
			if (ptr->key > ptr->next->key) {
				++n_move;
				K tmp_key = ptr->key;
				ptr->key = ptr->next->key;
				ptr->next->key = tmp_key;
				b = true;
			}
			ptr = ptr->next;
		}
		// ���ִ��һ��ɨ��֮��������Ԫ���Ѿ�����ֱ�ӷ���
		if (!b)
			break;
	}
}

template <typename K, typename V>
void element<K, V>::print() {
	auto tmp = this;
	while (tmp) {
		cerr << tmp->key << " ";
		tmp = tmp->next;
	}
	cerr << endl;
}

template <typename K, typename V>
void element<K, V>::insertsort(int &n_compare, int &n_move) {
	n_move = 0;
	// ���ֻ��һ��Ԫ�أ�����
	if (!next)
		return;
	n_compare = 1;
	if (key > next->key) {
		++n_move;
		// ��һ���ǽ�ǰ����Ԫ���ź���
		K tmp_key = key;
		V tmp_value = value;
		key = next->key;
		value = next->value;
		next->key = tmp_key;
		next->value = tmp_value;
	}
	auto beg = this, end = next, curr = next->next, mid = this,
		curr_end = next;
	while (curr) {
		if (key >= curr->key) {
			++n_move;
			// ������Ƚϵ�Ԫ��С�ڵ�һ��Ԫ�أ����䶨λ�ڵ�һ��
			++n_compare;
			K tmp_key = key;
			V tmp_value = value;
			key = curr->key;
			value = curr->value;
			end->next = curr->next;
			curr->key = tmp_key;
			curr->value = tmp_value;
			curr->next = next;
			next = curr;
			curr = end->next;
		}
		else if (end->key <= curr->key) {
			// ����������һ��Ԫ�أ��ŵ����һ��Ԫ�أ�ͬʱ�� end ���˳��һλ
			++n_compare;
			end = end->next;
			curr_end = end;
			curr = curr->next;
		}
		else {
			// ����ִ�ж�����������Ԫ�ز����Ѿ�����õ����е��ʵ�λ��
			while (true) {
				mid = &(*beg)[(*end - *beg) / 2];
				if ((*end - *beg) == 1) {
					++n_move;
					curr_end->next = curr->next;
					beg->next = curr;
					curr->next = end;
					end = curr_end;
					beg = this;
					curr = end->next;
					break;
				}
				else if (mid->key < curr->key) {
					++n_compare;
					beg = mid;
				}
				else {
					end = mid;
				}
			}
		}
	}
}

template <typename K, typename V>
void element<K, V>::select_sort(int &n_compare, int &n_move) {
	n_compare = 0;
	n_move = 0;
	// �� tmp ��¼��ǰ������Ԫ��
	auto tmp = this;
	while (tmp) {
		// min ��¼ tmp ֮����С��Ԫ��
		auto curr = tmp->next, min = tmp;
		while (curr) {
			// ���� curr��ֱ���ҵ���СԪ��
			++n_compare;
			if (curr->key < min->key)
				min = curr;
			curr = curr->next;
		}
		// ��ǰԪ�غ�֮�����СԪ�ؽ���
		++n_move;
		tmp->swap(min);
		// ������ǰԪ��
		tmp = tmp->next;
	}
}

template <typename K, typename V>
void element<K, V>::heap_sort(int &n_compare, int &n_move) {
	n_compare = 0;
	n_move = 0;
	auto ptr = this;
	int n = 1;
	// ͳ��Ԫ�ظ���
	while (ptr) {
		++n;
		ptr = ptr->next;
	}
	auto tmp = this;
	// ����һ����
	priorityQueue<K> p(n);
	// ������Ԫ��������
	while (tmp) {
		++n_move;
		p.add(tmp->key, n_compare);
		tmp = tmp->next;
	}
	tmp = this;
	// ���Ͻ����е���СԪ�س���
	while (p.n != 0) {
		++n_move;
		tmp->key = p.removeMin(n_compare);
		tmp = tmp->next;
	}
}

template <typename K, typename V>
void element<K, V>::swap(element<K, V> *ptr) {
	if (this == ptr)
		return;
	K tmp_k = key;
	V tmp_value = value;
	key = ptr->key;
	value = ptr->value;
	ptr->key = tmp_k;
	ptr->value = tmp_value;
}

template <typename K, typename V>
int element<K, V>::operator-(const element<K, V> &e) {
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

#endif