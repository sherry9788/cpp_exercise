// string2int.cpp : Defines the entry point for the console application.
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

int string2int(string s)
{
	int res(0);
	Stack<char> ST;
	for (int i = s.size() - 1; i >= 0; --i)
	{
		ST.push(s[i]);
	}

	while (!ST.isEmpty())
	{
		res = res * 10 + ST.info() - '0';
		ST.pop();
	}

	return res;
}

int main()
{
	return 0;
}
