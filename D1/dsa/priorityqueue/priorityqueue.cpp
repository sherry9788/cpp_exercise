#include <iostream>
#include <cassert>

using namespace std;

int power2(int n)
{
	if (n == 0)
		return 1;
	else
		return 2 * power2(n - 1);
}

template <typename T>
struct priorityqueue
{
	//data
public:
	int Max;
	int n;
	T *pq;
	//function
public:
	priorityqueue(int n_Max = 1023) :
		Max(n_Max), n(0)
	{
		pq = new T[Max];
	}

	~priorityqueue()
	{
		delete pq;
	}

	priorityqueue &operator=(priorityqueue &P)
	{
		n = P.n;
		Max = P.Max;
		pq = new T[Max];
		for (int i = 0; i < n; ++i)
			pq[i] = P.pq[i];
		return *this;
	}

	priorityqueue &add_heap(T x)
	{
		assert(n <= Max);
		int i;
		for (i = n; i > 0; i = (i - 1) / 2)
		{
			if (pq[(i - 1) / 2] < x)
			{
				pq[i] = x;
				break;
			}
			else
			{
				pq[i] = pq[(i - 1) / 2];
			}
		}
		if (i == 0)
			pq[i] = x;
		++n;
		return *this;
	}

	priorityqueue &print()
	{
		for (int layer = 1; power2(layer - 1) <= n; ++layer)
		{
			for (int i = power2(layer - 1) - 1; (i < power2(layer) - 1)
				&& i < n; ++i)
				cerr << pq[i] << " ";

			cerr << endl;
		}
		return *this;
	}

	priorityqueue & removeMin()
	{
		int i;
		for (i = 0; i * 2 + 2 < n;)
		{
			if (pq[i * 2 + 1] < pq[i * 2 + 2])
			{
				pq[i] = pq[i * 2 + 1];
				i = i * 2 + 1;
			}
			else
			{
				pq[i] = pq[i * 2 + 2];
				i = i * 2 + 2;
			}
		}

		pq[i] = pq[n - 1];
		if (i * 2 + 2 != n && pq[i] < pq[(i - 1) / 2])
		{
			T temp = pq[i];
			pq[i] = pq[(i - 1) / 2];
			pq[(i - 1) / 2] = temp;
		}
		--n;
		return *this;
	}

	bool isEmpty()
	{
		return n == 0;
	}
};



int main()
{
	priorityqueue<int> p1(1023);
	p1.add_heap(0).add_heap(1).add_heap(10).add_heap(2).add_heap(3)
		.add_heap(3).add_heap(20).add_heap(-1).add_heap(2).add_heap(4)
		.add_heap(212).add_heap(-100).add_heap(233).add_heap(22).add_heap(1);
	cerr << "successful" << endl;
	p1.print();
	while (!p1.isEmpty())
	{
		p1.removeMin();
		p1.print();
	}

	return 0;
}
