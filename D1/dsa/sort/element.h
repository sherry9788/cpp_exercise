#ifndef ELEMENT
#define ELEMENT

#include <iostream>
#include <cassert>
#include <random>
#include <ctime>

#include "priority_queue.h"

using namespace std;

// element 是一个模板类，是链表的链结
template <typename K, typename V>
struct element {
	// data
	// 关键码
	K key;
	// 值
	V value;
	// 指向下一个元素的指针
	element<K, V> *next = nullptr;
	// 指示是否被析构
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

	// 类似于指针的 [] 操作，可以定位到之后的某个链结
	element<K, V> &operator[](int n);

	// 返回两个链结之间的距离
	int operator-(const element<K, V> &e);

	// copy constructor
	element<K, V>(element<K, V> &E);

	// 添加一个元素到链表的末尾
	bool add(K n_key, V n_value = V());

	// 交换两个元素
	void swap(element<K, V> *ptr);

	// 冒泡排序，n_compare 记录比较次数
	void bubbleSort(int &n_compare, int &n_move);

	// 插入排序，n_compare 记录比较次数
	void insertsort(int &n_compare, int &n_move);

	// 选择排序，n_compare 记录比较次数
	void select_sort(int &n_compare, int &n_move);

	// 堆排序，n_compare 记录比较次数
	void heap_sort(int &n_compare, int &n_move);

	// 打印链表中的所有元素
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
	// b 用来记录是否已经有序
	bool b = false;
	// n 记录元素的个数
	int n = -1;
	// 统计元素个数
	while (ptr) {
		++n;
		ptr = ptr->next;
	}
	for (int i = n; i > 0; --i) {
		ptr = this;
		b = false;
		// 对前i个元素进行一次起泡排序
		// 即对每两个相邻的元素进行一次排序
		while (ptr != &(*this)[i]) {
			++n_compare;
			// 如果两个元素顺序反了，调换
			if (ptr->key > ptr->next->key) {
				++n_move;
				K tmp_key = ptr->key;
				ptr->key = ptr->next->key;
				ptr->next->key = tmp_key;
				b = true;
			}
			ptr = ptr->next;
		}
		// 如果执行一次扫描之后发现所有元素已经有序，直接返回
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
	// 如果只有一个元素，返回
	if (!next)
		return;
	n_compare = 1;
	if (key > next->key) {
		++n_move;
		// 这一步是将前两个元素排好序
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
			// 如果待比较的元素小于第一个元素，将其定位在第一个
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
			// 如果大于最后一个元素，放到最后一个元素，同时将 end 向后顺延一位
			++n_compare;
			end = end->next;
			curr_end = end;
			curr = curr->next;
		}
		else {
			// 否则执行二分搜索，将元素插入已经排序好的序列的适当位置
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
	// 用 tmp 记录当前操作的元素
	auto tmp = this;
	while (tmp) {
		// min 记录 tmp 之后最小的元素
		auto curr = tmp->next, min = tmp;
		while (curr) {
			// 递增 curr，直到找到最小元素
			++n_compare;
			if (curr->key < min->key)
				min = curr;
			curr = curr->next;
		}
		// 当前元素和之后的最小元素交换
		++n_move;
		tmp->swap(min);
		// 递增当前元素
		tmp = tmp->next;
	}
}

template <typename K, typename V>
void element<K, V>::heap_sort(int &n_compare, int &n_move) {
	n_compare = 0;
	n_move = 0;
	auto ptr = this;
	int n = 1;
	// 统计元素个数
	while (ptr) {
		++n;
		ptr = ptr->next;
	}
	auto tmp = this;
	// 创建一个堆
	priorityQueue<K> p(n);
	// 将所有元素添加入堆
	while (tmp) {
		++n_move;
		p.add(tmp->key, n_compare);
		tmp = tmp->next;
	}
	tmp = this;
	// 不断将堆中的最小元素出队
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