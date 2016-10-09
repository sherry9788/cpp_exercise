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

	void binSort() {
		if (!next)
			return;
		if (key > next->key) {
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
				end = end->next;
				curr_end = end;
				curr = curr->next;
			}
			else {
				while (true) {
					mid = &(*beg)[(*end - *beg) / 2];
					if ((*end - *beg) == 1) {
						curr_end->next = curr->next;
						beg->next = curr;
						curr->next = end;
						end = curr_end;
						beg = this;
						curr = end->next;
						break;
					}
					else if (mid->key < curr->key) {
						beg = mid;
					}
					else {
						end = mid;
					}
				}
			}
		}
	}
};

template <typename K, typename V>
ostream &operator<<(ostream &out, const element<K, V> &E) {
	out << E.key;
	return out;
}

int main() {
	element<int, int> e(1);
	int n;
loop:
	cin >> n;
	for (int i = 0; i < n; ++i)
		e.add(rand());
	int x = clock();
	e.binSort();
	e.print();
	goto loop;
	return 0;
}
