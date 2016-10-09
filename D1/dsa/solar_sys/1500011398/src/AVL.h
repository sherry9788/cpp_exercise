#ifndef AVL
#define AVL

#include "node.h"
#include "element.h"
#include "stack.h"

// calculate the "R" value
int cal_r(std::map<std::vector<int>, int> &C, int i, int j, int &r);

// the structure of a AVL bintree
 template <typename K, typename V>
struct bintree
{
	//data
public:
	K key;
	V value;
	bintree *m_L = nullptr;//left
	bintree *m_R = nullptr;//rgiht
	bool isFir = true;

	//function
public:

	// default constructor
	bintree<K, V>() = default;

	// constructor
	bintree<K, V>(K n_key, V n_value);
	
	// destructor
	~bintree<K, V>();

	// assignment function
	bintree<K, V> &operator=(bintree<K, V> &B);

	// copy constructor
	bintree<K, V>(bintree<K, V> &B);

	// find the value match the key
	V operator[](const K &n_key);

	// calculate the height
	int height();

	// calculate the difference between the two subtrees
	int diff();

	// add a element without AVL function
	bool normal_add(K n_key, V n_value);

	// adjust function
	void LL();

	void LR();

	void RL();

	void RR();

	// add a element using AVL function
	void add(K n_key, V n_value);
};

 template <typename K, typename V>
bintree<K, V>::bintree(K n_key, V n_value) :
	key(n_key), value(n_value), isFir(false) {}

 template <typename K, typename V>
bintree<K, V>::~bintree() {
	if (m_R != nullptr)
		delete m_R;

	if (m_L != nullptr)
		delete m_L;
}

 template <typename K, typename V>
bintree<K, V> &bintree<K, V>::operator=(bintree<K, V> &B) {
	key = B.key;
	value = B.value;
	if (B.m_R != nullptr) {
		m_R = new bintree<K, V>();
		*m_R = *B.m_R;
	}

	if (B.m_L != nullptr) {
		m_L = new bintree<K, V>();
		*m_L = *B.m_L;
	}
}

 template <typename K, typename V>
bintree<K, V>::bintree(bintree<K, V> &B) {
	key = B.key;
	value = B.value;
	if (B.m_R != nullptr)
		m_R = new bintree<K, V>(*B.m_R);

	if (B.m_L != nullptr)
		m_L = new bintree<K, V>(*B.m_L);
}

 template <typename K, typename V>
int bintree<K, V>::height() {
	if (m_R == nullptr && m_L == nullptr)
		return 1;
	else {
		int L_H(0), R_H(0);
		if (m_R != nullptr)
			R_H = m_R->height();
		if (m_L != nullptr)
			L_H = m_L->height();
		if (R_H > L_H)
			return R_H + 1;
		else
			return L_H + 1;
	}
}

 template <typename K, typename V>
int bintree<K, V>::diff() {
	int L_H(0), R_H(0);
	if (m_L != nullptr)
		L_H = m_L->height();
	if (m_R != nullptr)
		R_H = m_R->height();
	return L_H - R_H;
}

 template <typename K, typename V>
bool bintree<K, V>::normal_add(K n_key, V n_value) {
	if (isFir == true) {
		isFir = false;
		key = n_key;
		value = n_value;
		return false;
	}
	bintree<K, V>* tmp = this;
	while (true) {
		if (tmp->key > n_key) {
			if (tmp->m_L == nullptr) {
				tmp->m_L = new bintree<K, V>(n_key, n_value);
				return true;
			}
			else
				tmp = tmp->m_L;
		}
		else if (tmp->key < n_key) {
			if (tmp->m_R == nullptr) {
				tmp->m_R = new bintree<K, V>(n_key, n_value);
				return true;
			}
			else
				tmp = tmp->m_R;
		}
		else {
			tmp->value = n_value;
			return true;
		}
	}
}

 template <typename K, typename V>
void bintree<K, V>::LL() {
	auto ptr_a = m_R, ptr_b = m_L->m_R, ptr_c = m_L->m_L;
	element<K, V> ele_A(key, value);
	key = m_L->key;
	value = m_L->value;
	m_L->m_L = nullptr;
	m_L->m_R = nullptr;
	delete m_L;
	m_R = new bintree<K, V>(ele_A.key, ele_A.value);
	m_L = ptr_c;
	m_R->m_L = ptr_b;
	m_R->m_R = ptr_a;
}

 template <typename K, typename V>
void bintree<K, V>::LR() {
	element<K, V> ele_A(m_L->key, m_L->value), ele_B(key, value),
		ele_C(m_L->m_R->key, m_L->m_R->value);
	auto ptr_a = m_L->m_L, ptr_b = m_L->m_R->m_L,
		ptr_c = m_L->m_R->m_R, ptr_d = m_R;
	m_L->m_R->m_L = nullptr;
	m_L->m_R->m_R = nullptr;
	delete m_L->m_R;
	m_L->m_L = nullptr;
	m_L->m_R = nullptr;
	delete m_L;
	key = ele_C.key;
	value = ele_C.value;
	m_L = new bintree<K, V>(ele_A.key, ele_A.value);
	m_R = new bintree<K, V>(ele_B.key, ele_B.value);
	m_L->m_L = ptr_a;
	m_L->m_R = ptr_b;
	m_R->m_L = ptr_c;
	m_R->m_R = ptr_d;
}

 template <typename K, typename V>
void bintree<K, V>::RL() {
	element<K, V> ele_A(key, value), ele_B(m_R->key, m_R->value),
		ele_C(m_R->m_L->key, m_R->m_L->value);
	auto ptr_a = m_L, ptr_b = m_R->m_L->m_L,
		ptr_c = m_R->m_L->m_R, ptr_d = m_R->m_R;
	m_R->m_L->m_L = nullptr;
	m_R->m_L->m_R = nullptr;
	delete m_R->m_L;
	m_R->m_L = nullptr;
	m_R->m_R = nullptr;
	delete m_R;
	key = ele_C.key;
	value = ele_C.value;
	m_L = new bintree<K, V>(ele_A.key, ele_A.value);
	m_R = new bintree<K, V>(ele_B.key, ele_B.value);
	m_L->m_L = ptr_a;
	m_L->m_R = ptr_b;
	m_R->m_L = ptr_c;
	m_R->m_R = ptr_d;
}

 template <typename K, typename V>
void bintree<K, V>::RR() {
	auto ptr_a = m_L, ptr_b = m_R->m_L, ptr_c = m_R->m_R;
	element<K, V> ele_A(key, value);
	key = m_R->key;
	value = m_R->value;
	m_R->m_L = nullptr;
	m_R->m_R = nullptr;
	delete m_R;
	m_L = new bintree<K, V>(ele_A.key, ele_A.value);
	m_R = ptr_c;
	m_L->m_L = ptr_a;
	m_L->m_R = ptr_b;
}

 template <typename K, typename V>
void bintree<K, V>::add(K n_key, V n_value) {
	if (!normal_add(n_key, n_value))
		return;
	auto tmp = this;
	bintree<K, V> *min = nullptr;
	while (true) {
		if (tmp->diff() < -1 || tmp->diff() > 1)
			min = tmp;
		if (n_key < tmp->key)
			tmp = tmp->m_L;
		else if (n_key > tmp->key)
			tmp = tmp->m_R;
		else
			break;
	}

	if (min == nullptr)
		return;

	if (min->diff() == 2) {
		if (min->m_L->diff() > 0)
			min->LL();
		else
			min->LR();
	}
	else {
		if (min->m_R->diff() > 0)
			min->RL();
		else
			min->RR();
	}
}

template <typename K, typename V>
V bintree<K, V>::operator[](const K &n_key) {
	bintree<K, V> *curr = this;
	while (curr != nullptr && curr->key != n_key) {
		if (n_key < curr->key)
			curr = curr->m_L;
		else if (n_key > curr->key)
			curr = curr->m_R;
	}

	if (curr == nullptr) {
		std::cerr << "Can't find the element" << std::endl;
		return V();
	}

	return curr->value;
}

#endif AVL