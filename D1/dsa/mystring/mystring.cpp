// mystring.cpp : Defines the entry point for the console application.
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

int main()
{
    return 0;
}

