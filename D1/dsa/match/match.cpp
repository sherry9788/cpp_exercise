// match.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

class my_string
{
	friend ostream &operator<<(ostream &out, const my_string &s);
	friend istream &operator >> (istream &in, my_string &s);
	//data
private:
	char info;
	size_t size;
	my_string *next = 0;

	static size_t m_size;
	//function
private:
	my_string(size_t n_size, char n_info);
public:
	my_string() = default;
	my_string(size_t n_size);
	my_string(const char *c);
	my_string(const string str);

	char &operator[](int seq);

	size_t getsize();

	~my_string();


};

size_t my_string::m_size = 0;

my_string::my_string(size_t n_size)
{
	info = 0;
	if (m_size == 0)
		m_size = n_size;
	size = m_size;
	if (n_size == 0)
		m_size = 0;
	else
		next = new my_string(n_size - 1);
}

my_string::my_string(size_t n_size, char n_info) :
	info(n_info), size(n_size) {}

my_string::my_string(const char *c)
{
	size = 0;
	info = 0;

	for (const char *temp = c; *temp != 0; ++temp)
		++size;

	my_string *temp = this;

	while (*c != 0)
	{
		temp->next = new my_string(size, *c);
		temp = temp->next;
		++c;
	}
}

my_string::my_string(const string str)
{
	size = str.size();
	info = 0;

	my_string *temp = this;

	for (unsigned i = 0; i < size; ++i)
	{
		temp->next = new my_string(size, str[i]);
		temp = temp->next;
	}
}

my_string::~my_string()
{
	if (next != 0)
		delete next;
}

char &my_string::operator [](int seq)
{
	my_string *temp = this;
	if (seq >= 0 && seq < (int)size)
		for (int i = 0; i < seq + 1; ++i)
			temp = temp->next;
	else
		return this->info;
	return temp->info;
}

size_t my_string::getsize()
{
	return size;
}

ostream &operator<<(ostream &out, const my_string &s)
{
	const my_string *temp = &s;
	for (size_t i = 0; i < s.size; ++i)
	{
		temp = temp->next;
		out << temp->info;
	}
	return out;
}

istream &operator >> (istream &in, my_string &s)
{
	delete s.next;
	string str;
	in >> str;
	s.size = str.size();
	s.info = 0;

	my_string *temp = &s;

	for (unsigned i = 0; i < s.size; ++i)
	{
		temp->next = new my_string(s.size, str[i]);
		temp = temp->next;
	}
	return in;
}

int plain_match(my_string text, my_string target)
{
	size_t n = text.getsize() - target.getsize() + 1;
	size_t step = target.getsize();
	size_t i, j;
	if (step > n + step)
		return -1;
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < step; ++j)
			if (target[j] != text[i + j])
				goto posi;
		return i;
	posi:;
	}
	return -1;
}

int match(my_string text, my_string target)
{
	size_t step = target.getsize();

	unsigned *skip = new unsigned[target.getsize()];
	/*
	{
	int i, j, k;
	for(i = 0; i < (int)target.getsize(); ++ i)
	{
	for(j = 0; j < i + 1; ++ j)
	{
	for(k = 0; k < i - j + 1; ++ k)
	{
	if(k != i - j)
	{
	if(target[k] != target[k + j])
	goto posi_1;
	}
	else
	if(target[k] == target[k + j])
	goto posi_1;
	}//for k
	skip[i] = j + 1;
	break;
	posi_1:
	if(j == i)
	skip[i] = i + 1;
	}//for j
	}//for i
	}


	skip[0] = 1;
	for(int i = 1; i < step; ++ i)
	{
	while()
	}

	size_t n = text.getsize() - target.getsize() + 1;
	size_t i, j;
	if(step > n + step)
	return -1;
	for(i = 0; i < n;)
	{
	for(j = 0; j < step; ++ j)
	if(target[j] != text[i + j])
	{
	goto posi_2;
	}
	return i;
	posi_2:
	i += skip[j];
	}
	*/

	skip[0] = 0;
	unsigned k = 0;
	for (unsigned i = 1; i < step; ++i)
	{
		while (target[i] != target[k])
			k = skip[k];
		++k;
		skip[i] = k;
	}

	for (unsigned m = 0; m < step; ++m)
		cout << skip[m] << endl;

	unsigned i = 0, j;

	for (j = 0; i < text.getsize() - step && j < step; ++i, ++j)
	{
		if (target[j] != text[i])
		{
			j = skip[j];
		}
	}

	if (j == step)
		return i;

	return -1;
}

int main()
{
	return 0;
}
