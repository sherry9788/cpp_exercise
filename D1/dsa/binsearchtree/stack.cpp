#include "stack.h"

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
