#ifndef HASHTABLE
#define HASHTABLE

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "element.h"

using namespace std;

// It's a structor named HashTable
 template <typename K, typename V>
struct HashTable
{
	// data
public:
	// the capacity
	int m = 0;						
	// the number of the collision
	int n_collision = 0;			
	// the position of the collision
	vector<int> position_collision; 
	// the elements
	element<K, V> *ele = nullptr;	

	// function
public:
	// default constructor
	HashTable() = default;

	// constructor
	HashTable(int n_m);

	// destructor
	~HashTable();

	// copy constructor
	HashTable(HashTable &H);

	// assignment
	HashTable &operator=(HashTable &H);

	// search function
	V operator[](K n_key);

	// delete function
	V del(K n_key);

	// hash function
	int h(K n_key);

	// linear search function
	bool linear_search(K n_key, int &pos);

	// insert function
	void insert(K n_key, V n_value);

	// insert function
	void insert(element<K, V> n_ele);
};

 template <typename K, typename V>
HashTable<K, V>::HashTable(int n_m) {
	m = n_m;
	ele = new element<K, V>[m];
	// if it is not allocated space, kill the program
	assert(ele);
	// reset all key value;
	for (int i = 0; i < m; ++i)
		ele[i] = element<K, V>();
}

 template <typename K, typename V>
HashTable<K, V>::~HashTable() {
	delete[]ele;
}

 template <typename K, typename V>
HashTable<K, V>::HashTable(HashTable &H) {
	m = H.m;
	n_collision = H.n_collision;
	for (int i = 0; i < m; ++i)
		ele[i] = H.ele[i];
}

 template <typename K, typename V>
HashTable<K, V> &HashTable<K, V>::operator=(HashTable &H) {
	if (ele)
		delete[]ele;
	m = H.m;
	n_collision = H.n_collision;
	for (int i = 0; i < m; ++i)
		ele[i] = H.ele[i];
	return *this;
}

 template <typename K, typename V>
V HashTable<K, V>::operator[](K n_key) {
	int index = h(n_key);
	// use ini to record the hash value
	int ini = index;
	if (ele[index].key == n_key)
		// if it is found, return true
		return ele[index].value;
	// or find a position that match the n_key
	for (++index; index != ini; ++index) {
		index %= m;
		if (ele[index].key == n_key)
			return ele[index].value;
	}
	// can't found!
	return V();
}

 template <typename K, typename V>
int HashTable<K, V>::h(K n_key) {
	return (n_key + 10000 * m) % m;
}

 template <typename K, typename V>
bool HashTable<K, V>::linear_search(K n_key, int &pos) {
	int index = h(n_key);
	int ini = index;
	if (ele[index].key == K()) {
		pos = index;
		return true;
	}
	// if there is a collision, record plus 1
	++n_collision;
	// record the position of the collision
	position_collision.push_back(pos);
	// find the next position
	for (++index; index != ini; ++index) {
		index %= m;
		if (ele[index].key == K()) {
			pos = index;
			return true;
		}
	}
	// the hash table is full
	return false;
}

 template <typename K, typename V>
void HashTable<K, V>::insert(K n_key, V n_value) {
	int pos = 0;
	// if the hash table is full, kill the program
	assert(linear_search(n_key, pos));
	ele[pos].key = n_key;
	ele[pos].value = n_value;
}

 template <typename K, typename V>
void HashTable<K, V>::insert(element<K, V> n_ele) {
	insert(n_ele.key, n_ele.value);
}

 template <typename K, typename V>
V HashTable<K, V>::del(K n_key) {
	// use ret to record the value to return
	V ret;
	int index = h(n_key);
	int ini = index;
	// if it is found, return it
	if (ele[index].key == n_key)
		ret = ele[index].value;
	else {
		// look for it
		for (++index; index != ini; ++index) {
			index %= m;
			if (ele[index].key == n_key)
				ret = ele[index].value;
		}
		// there isn't such a element
		if (index == ini)
			return V();
	}

	// use space to record the position of the space
	int space = index;
	// use next_space to record the position of the next sapce 
	int next_space = index + 1;
	// look for the next space
	while (ele[next_space].key != K()) {
		++next_space;
		if (next_space == m)
			next_space = 0;
	}

	// delete the key value
	ele[index].key = K();

	++index;
	if (index == m)
		index = 0;

	if (next_space < index)
		// if it is a loop
		while (index != next_space) {
			if (h(ele[index].key) < space) {
				// if we can't find the current element
				ele[space].key = ele[index].key;
				ele[space].value = ele[index].value;
				// move the space
				space = index;
			}
			++index;
			// find a loop
			if (index == m)
				index = 0;
		}
	else
		// if there isn't a loop
		while (index != next_space) {
			if (h(ele[index].key) < space || h(ele[index].key) > next_space) {
				// if we can't find the current element
				ele[space].key = ele[index].key;
				ele[space].value = ele[index].value;
				// move the space
				space = index;
			}
			++index;
		}

	return ret;
}

#endif