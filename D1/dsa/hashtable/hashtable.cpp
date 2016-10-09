#include <iostream>
#include <cassert>

using namespace std;

template <typename K, typename V>
struct element
{
	K key;
	V value;
};

template <typename K, typename V>
struct HashTable
{
	//data
public:
	int m = 0;
	element<K, V> *ele = nullptr;

	//function
public:
	HashTable() = default;

	HashTable(int n_m) {
		m = n_m;
		ele = new element<K, V>[m];
		assert(ele);
		for (int i = 0; i < m; ++i)
			ele[i].key = element<K, V>();
	}

	~HashTable() {
		delete []ele;
	}

	HashTable(HashTable &H) {
		m = H.m;
		for (int i = 0; i < m; ++i)
			ele[i] = H.ele[i];
	}

	HashTable &operator=(HashTable &H) {
		if (ele)
			delete ele;
		m = H.m;
		for (int i = 0; i < m; ++i)
			ele[i] = H.ele[i];
		return *this;
	}

	V operator[](K n_key) {
		int index = h(n_key);
		int ini = index;
		if (ele[index].key == n_key)
			return ele[index].value;
		for (++index; index != ini; ++index) {
			index %= m;
			if (ele[index].key == n_key)
				return ele[index].value;
		}
		cerr << "Not Found" << endl;
		return 0;
	}

	int h(K n_key) {
		return n_key % m;
	}

	bool linear_search(K n_key, int &pos) {
		int index = h(n_key);
		int ini = index;
		if (ele[index].key == n_key) {
			pos = index;
			return true;
		}
		for (++index; index != ini; ++index) {
			index %= m;
			if (ele[index].key == n_key) {
				pos = index;
				return true;
			}
			if (ele[index] == V())
				return false;
		}
		return false;
	}

	void insert(K n_key, V n_value) {
		int pos;
		assert(linear_search(n_key, pos));
		ele[pos].key = n_key;
		ele[pos].value = n_value;
	}

	void insert(element<K, V> n_ele) {
		insert(n_ele.key, n_ele.value);
	}
};

int main()
{
	HashTable<int, int> HT(20);
	for (int i = 0; i < 10; ++i)
		HT.insert(i, i * 10);
	for (int i = 30; i < 50; i += 2)
		HT.insert(i, i * 10);
	for (int i = 0; i < 10; ++i)
		cerr << HT[i] << endl;
	for (int i = 30; i < 50; i += 2)
		cerr << HT[i] << endl;
	return 0;
}
