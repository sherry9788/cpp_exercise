// bitset.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
    return 0;
}

#include <iostream>
#include <cassert>

using namespace std;

struct bitset
{
	//data
	int size;
	char *array;

	//function
	bitset() = default;
	bitset(int n_size)
	{
		size = (n_size + 7) / 8;
		array = new char[size];
		for (int i = 0; i < size; ++i)
			array[i] = 0;
	}

	virtual ~bitset()
	{
		delete array;
	}

	virtual bitset &operator=(bitset &B)
	{
		size = B.size;
		array = new char[size];
		for (int i = 0; i < size; ++i)
			array[i] = B.array[i];
		return *this;
	}
};

int seq(const char &c)
{
	if (c >= 'a' && c <= 'z')
		return c - 'a';
	else if (c >= 'A' && c <= 'Z')
		return c - 'A' + 26;
	else
		return -1;
}

struct alphabet : public bitset
{
	//function
public:
	alphabet()
	{
		size = 7;
		array = new char[7];
		for (int i = 0; i < 7; ++i)
			array[i] = 0;
	}

	alphabet &add(const char &c)
	{
		int num = seq(c);
		assert(num >= 0);
		int index = num / 8;
		num = num % 8;
		char tmp = 1;
		array[index] |= (tmp << num);
		return *this;
	}

	bool isMember(const char &c)
	{
		int num = seq(c);
		int index = num / 8;
		num = num % 8;
		char tmp = 1;
		return (array[index] & (tmp << num)) != 0;
	}

	alphabet &del(const char &c)
	{
		int num = seq(c);
		int index = num / 8;
		num %= 8;
		char tmp = 1;
		array[index] ^= (tmp << num);
		return *this;
	}

	alphabet *unionSet(const alphabet &A)
	{
		alphabet *ret = new alphabet();
		for (int i = 0; i < 7; ++i)
			ret->array[i] = array[i] | A.array[i];
		return ret;
	}

	alphabet *intersectionSet(const alphabet &A)
	{
		alphabet *ret = new alphabet();
		for (int i = 0; i < 7; ++i)
			ret->array[i] = array[i] & A.array[i];
		return ret;
	}

	alphabet *differenceSet(const alphabet &A)
	{
		alphabet *ret = new alphabet();
		for (int i = 0; i < 7; ++i)
			ret->array[i] = array[i] & ~A.array[i];
		return ret;
	}
};

int main()
{
	alphabet x, y;
	x.add('A').add('Z').add('m').add('c').add('e');
	y.add('S').add('M').add('s').add('c').add('i');
	alphabet *temp1 = x.unionSet(y);
	assert(temp1->isMember('c'));
	assert(temp1->isMember('i'));
	assert(temp1->isMember('Z'));
	alphabet *temp2 = x.intersectionSet(y);
	assert(temp2->isMember('c'));
	assert(!temp2->isMember('s'));
	assert(!temp2->isMember('A'));
	alphabet *temp3 = x.differenceSet(y);
	assert(temp3->isMember('A'));
	assert(!temp3->isMember('c'));
	assert(!temp3->isMember('M'));
	cerr << "All test success" << endl;
	return 0;
}
