#include "binsearchtree.h"

 template <typename K, typename V>
bintree<K, V>::bintree(const vector<element<K, V> > &ve,
	vector<int> &p, vector<int> &q) {
	map<vector<int>, int> R, C, W;

	int size = ve.size();

	for (int i = 0; i < size + 1; ++i) {
		for (int j = 0; j < size + 1; ++j) {
			for (int k = i; k <= j; ++k)
				W[seq{ i, j }] += q[k];
			for (int k = i; k < j; ++k)
				W[seq{ i, j }] += p[k];
		}
	}

	for (int step = 1; step < size + 1; ++step) {
		for (int ini = 0; ini < size - step + 1; ++ini) {
			C[seq{ ini, ini + step }] = W[seq{ ini, ini + step }] +
				cal_r(C, ini, ini + step, R[seq{ ini, ini + step }]);
		}
	}

	Stack<seq> Stack_Root;
	Stack_Root.push(seq{ 0, size });
	while (!Stack_Root.isEmpty()) {
		seq tmp = Stack_Root.info();
		(*this)[ve[R[tmp] - 1].key] = ve[R[tmp] - 1].value;
		Stack_Root.pop();
		if (tmp[1] > R[tmp])
			Stack_Root.push(seq{ R[tmp], tmp[1] });
		if (tmp[0] < R[tmp] - 1)
			Stack_Root.push(seq{ tmp[0], R[tmp] - 1 });

	}
}

template <typename K, typename V>
bintree<K, V>::~bintree()
{
	if (m_R != nullptr)
		delete m_R;

	if (m_L != nullptr)
		delete m_L;
}

template <typename K, typename V>
bintree<K, V> &bintree<K, V>::operator=(bintree<K, V> &B)
{
	key = B.key;
	value = B.value;
	if (B.m_R != nullptr)
	{
		m_R = new bintree<K, V>();
		*m_R = *B.m_R;
	}

	if (B.m_L != nullptr)
	{
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
bool bintree<K, V>::delL()
{
	if (m_L == nullptr)
		return false;

	delete m_L;
	m_L = nullptr;
	return true;
}

template <typename K, typename V>
bool bintree<K, V>::delR()
{
	if (m_R == nullptr)
		return false;

	delete m_R;
	m_R = nullptr;
	return false;
}

template <typename K, typename V>
bintree<K, V> &bintree<K, V>::setL(K n_key, V n_value)
{
	delL();
	m_L = new bintree<K, V>(n_key, n_value);
	return *m_L;
}

template <typename K, typename V>
bintree<K, V> &bintree<K, V>::setR(K n_key, V n_value)
{
	delR();
	m_R = new bintree<K, V>(n_key, n_value);
	return *m_R;
}

template <typename K, typename V>
int son()
{
	return ((m_R != nullptr) + (m_L != nullptr));
}

template <typename K, typename V>
bool bintree<K, V>::isLeave()
{
	return son() == 0;
}

template <typename K, typename V>
vector<element<K, V> > bintree<K, V>::searchtree()
{
	vector<element<K, V> > ve;
	Stack<bintree<K, V> *> SB;
	bintree<K, V> *b;
	b = this;
	do
	{
		while (b != nullptr)
		{
			SB.push(b);
			b = b->m_L;
		}

		do
		{
			b = SB.pop();
			ve.push_back(element<K, V>(b->key, b->value));
		} while (b->m_R == nullptr && !SB.isEmpty());

		b = b->m_R;
	} while (!SB.isEmpty() || b != nullptr);
	return ve;
}

template <typename K, typename V>
V &bintree<K, V>::operator[](K n_key) {
	if (isFir == true) {
		isFir = false;
		key = n_key;
		return value;
	}
	bintree<K, V>* tmp = this;
	while (true) {
		if (tmp->key > n_key) {
			if (tmp->m_L == nullptr) {
				tmp->m_L = new bintree<K, V>(n_key, 0);
				return tmp->m_L->value;
			}
			else
				tmp = tmp->m_L;
		}
		else if (tmp->key < n_key) {
			if (tmp->m_R == nullptr) {
				tmp->m_R = new bintree<K, V>(n_key, 0);
				return tmp->m_R->value;
			}
			else
				tmp = tmp->m_R;
		}
		else {
			return tmp->value;
		}
	}
}

template <typename K, typename V>
bintree<K, V> *bintree<K, V>::enhance_equal_probability() {
	vector<element<K, V> > ve = searchtree();

	for (auto iter = ve.begin(); iter != ve.end(); ++iter)
		for (auto iter_1 = iter; iter_1 != ve.end(); ++iter_1)
			if (iter_1->key < iter->key) {
				auto x = *iter_1;
				*iter_1 = *iter;
				*iter = x;
			}

	bintree<K, V> *new_bintree = new bintree<K, V>
		(ve[(ve.begin() - ve.end()) / 2 + 1].key,
			ve[(ve.begin() - ve.end()) / 2 + 1].value);

	for (auto curr = ve.begin(); curr != ve.end(); ++curr) {
		auto beg = ve.begin(), en = ve.end(), mid = ve.end();
		while (mid != curr) {
			mid = beg + (en - beg) / 2;
			(*new_bintree)[mid->key] = mid->value;
			if (mid > curr)
				en = mid;
			else if (mid < curr)
				beg = mid;
		}
	}
	return new_bintree;
}

template <typename K, typename V>
ostream &operator<<(ostream &out, bintree<K, V> &b) {
	out << b.key;
	return out;
}

bool test(bintree<int, int> *b)
{
	auto tmp = b;
loop:

	int i;
	cin >> i;

	if (i == 0) {
		if (tmp)
			cerr << *tmp << endl;
		tmp = b;
	}
	else if (i == 1)
	{
		tmp = tmp->m_L;
	}
	else if (i == 2)
	{
		tmp = tmp->m_R;
	}
	else
		return 0;

	goto loop;
}

int cal_r(map<vector<int>, int> &C, int i, int j, int &r) {
	int ret;
	assert(j >= i);
	int curr = INT_MAX;
	for (ret = i + 1; ret <= j; ++ret) {
		if (C[vector<int>{ i, ret - 1 }] + C[vector<int>{ ret, j }] < curr) {
			curr = C[vector<int>{ i, ret - 1 }] + C[vector<int>{ ret, j }];
			r = ret;
		}
	}
	return curr;
}
