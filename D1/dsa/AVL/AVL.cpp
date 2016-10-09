#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <map>
#include <climits>
#include <ctime>

using namespace std;
using seq = vector<int>;

template <typename T>
struct Node
{
	T info;
	Node *next;

	Node(T x, Node *n_next);
};

template <typename T>
Node<T>::Node(T x, Node *n_next)
{
	info = x;
	next = n_next;
}

template <typename T>
struct Stack
{
	Node<T> *top;

	Stack();

	bool push(T x);
	T pop();

	bool isEmpty();
	T &info();
};

template <typename T>
T &Stack<T>::info()
{
	return top->info;
}

template <typename T>
Stack<T>::Stack()
{
	this->top = nullptr;
}

template <typename T>
bool Stack<T>::isEmpty()
{
	return top == nullptr;
}

template <typename T>
bool Stack<T>::push(T x)
{
	Node<T> *p = new Node<T>(x, this->top);
	if (p == NULL)
	{
		cout << "Out of space" << endl;
		return false;
	}
	else
		this->top = p;

	return true;
}

template <typename T>
T Stack<T>::pop()
{
	T tmp = top->info;
	Node<T> *p = top;
	top = p->next;
	delete p;

	return tmp;
}

template <typename K, typename V>
struct element
{
	K key;
	V value;
	element(K n_key, V n_value) :
		key(n_key), value(n_value) {}
};

int cal_r(map<seq, int> &C, int i, int j, int &r) {
	int ret;
	assert(j >= i);
	int curr = INT_MAX;
	for (ret = i + 1; ret <= j; ++ret) {
		if (C[seq{ i, ret - 1 }] + C[seq{ ret, j }] < curr) {
			curr = C[seq{ i, ret - 1 }] + C[seq{ ret, j }];
			r = ret;
		}
	}
	return curr;
}

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

	bintree<K, V>() = default;
	bintree<K, V>(K n_key, V n_value) :
		key(n_key), value(n_value), isFir(false) {}

	~bintree<K, V>()
	{
		if (m_R != nullptr)
			delete m_R;

		if (m_L != nullptr)
			delete m_L;
	}

	bintree<K, V> &operator=(bintree<K, V> &B)
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

	bintree<K, V>(bintree<K, V> &B) {
		key = B.key;
		value = B.value;
		if (B.m_R != nullptr)
			m_R = new bintree<K, V>(*B.m_R);

		if (B.m_L != nullptr)
			m_L = new bintree<K, V>(*B.m_L);
	}

	int height() {
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

	int diff() {
		int L_H(0), R_H(0);
		if (m_L != nullptr)
			L_H = m_L->height();
		if (m_R != nullptr)
			R_H = m_R->height();
		return L_H - R_H;
	}

	bool normal_add(K n_key, V n_value) {
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

	void LL() {
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

	void LR() {
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

	void RL() {
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

	void RR() {
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

	void add(K n_key, V n_value) {
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
};

template <typename K, typename V>
ostream &operator<<(ostream &out, bintree<K, V> &b) {
	out << b.height();
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

int main()
{
	bintree<int, int> b;
	double x = time(NULL);
	for (int i = 0; i < 1000; ++i)
		b.add(i, i * 10);
	cerr << time(NULL) - x << endl;
	test(&b);
	return 0;
}
