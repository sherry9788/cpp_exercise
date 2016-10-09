#include <iostream>
#include <climits>

using namespace std;

template <typename K, typename V>
struct ele
{
	//data
	K key;
	V value;

	//function
	ele(K n_key, V n_value) :
		key(n_key), value(n_value) {}
	ele() = default;
};

template <typename K, typename V>
struct dict
{
	//data
	ele<K, V> *Dic;
	size_t Max;
	size_t n;

	//function
	dict<K, V>(size_t n_Max = INT_MAX)
	{
		Max = n_Max;
		n = 0;
		Dic = new ele<K, V>[Max];
	}

	~dict()
	{
		delete Dic;
	}

	dict &operator=(const dict &D)
	{
		Max = D.Max;
		n = D.n;
		for (int i = 0; i < n; ++i)
			Dic[i] = D.Dic[i];
		return *this;
	}

	dict<K, V> &insert_ele(K key, V value)
	{
		int i;
		for (i = 0; i < n; ++i)
		{
			if (Dic[i].key > key)
				break;
		}

		for (int j = n; j > i; --j)
			Dic[j] = Dic[j - 1];

		Dic[i] = ele<K, V>(key, value);

		++n;

		return *this;
	}

	dict<K, V> &print()
	{
		for (int i = 0; i < n; ++i)
			cerr << Dic[i].key << " " << Dic[i].value << endl;
		return *this;
	}

	V &operator[](K key)
	{
		int n1 = 0, n2 = n;
		while (n1 != n2)
		{
			int mid = (n1 + n2) / 2;
			if (Dic[mid].key > key)
				n2 = mid;
			else if (Dic[mid].key < key)
				n1 = mid;
			else
				return Dic[mid].value;
		}
		return Dic[0].value;
	}

};

int main()
{
	dict<int, int> MD(1000);
	for (int i = 0; i < 11; ++i)
		MD.insert_ele(i, 10 * i);
	MD.print();
	for (int i = 0; i < 11; ++i)
	{
		cerr << MD[i] << endl;
	}
	return 0;
}
