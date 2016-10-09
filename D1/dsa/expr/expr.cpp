// expr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cstring>
#include <cstdlib>

//#define PRINT

using namespace std;

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
	bool pop();

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
bool Stack<T>::pop()
{
	if (isEmpty())
		return false;
	Node<T> *p = top;
	top = p->next;
	delete p;

	return true;
}

bool isSym(const char &c)
{
	return (c == '-' || c == '+' || c == '*' || c == '/');
}

string convert2rear(const string &ini)
{
	string res;
	Stack<char> *ST = new Stack<char>;
	for (unsigned i = 0; i < ini.size();)
	{
		if (isSym(ini[i]) || ini[i] == '(')
			ST->push(ini[i++]);

		else if (isdigit(ini[i]))
		{
			while (i < ini.size() && isdigit(ini[i]))
				res += ini[i++];

			res += ' ';

			if (!(ST->isEmpty()) && isSym(ST->info()))
			{
				res += ST->info();
				res += ' ';
				ST->pop();
			}
		}
		else if (ini[i++] == ')')
		{
			if (!(ST->isEmpty()) && isSym(ST->info()))
			{
				res += ST->info();
				res += ' ';
				ST->pop();
			}
			ST->pop();

			if (!(ST->isEmpty()) && isSym(ST->info()))
			{
				res += ST->info();
				res += ' ';
				ST->pop();
			}
		}
		else
		{
			cerr << "WTF?" << endl;
			return 0;
		}

	}

	return res;
}

double CalRearExpr(const string &str)
{
	Stack<double> *ST = new Stack<double>;
	unsigned i = 0;
	while (i < str.size())
		if (isdigit(str[i]))
		{
			int temp(0);
			while (i < str.size() && isdigit(str[i]))
				temp = temp * 10 + str[i++] - '0';
			ST->push(temp);
		}
		else
		{
			if (str[i] == '+')
			{
				double temp = ST->info();
				ST->pop();
				ST->info() += temp;
			}
			else if (str[i] == '-')
			{
				double temp = ST->info();
				ST->pop();
				ST->info() -= temp;
			}
			else if (str[i] == '*')
			{
				double temp = ST->info();
				ST->pop();
				ST->info() *= temp;
			}
			else if (str[i] == '/')
			{
				double temp = ST->info();
				ST->pop();
				ST->info() /= temp;
			}

			++i;
		}

	return ST->info();
}

int main()
{
    return 0;
}

