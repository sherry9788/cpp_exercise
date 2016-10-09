#include <iostream>
#include <cassert>
#include <random>
#include <ctime>

using namespace std;

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

	void bubbleSort() {
		auto ptr = this;
		bool b = false;
		int n = -1;
		while (ptr) {
			++n;
			ptr = ptr->next;
		}
		for (int i = n; i > 0; --i) {
			ptr = this;
			b = false;
			while (ptr != &(*this)[i]) {
				if (ptr->key > ptr->next->key) {
					K tmp_key = ptr->key;
					ptr->key = ptr->next->key;
					ptr->next->key = tmp_key;
					b = true;
				}
				ptr = ptr->next;
			}
			if (!b)
				break;
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
	e.bubbleSort();
	e.print();
	goto loop;
	return 0;
}
