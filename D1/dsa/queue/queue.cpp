// queue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>

#define PRINT

using namespace std;

template <typename T> class link
{
public:
	//data
	T info; //info 是循环链表的储存信息，写成了模板类方便在使用过程中更改数据类型
	int loop_num; //loop_num 是这个循环链表的链结数，默认为1
	link *prev, *next;  //prev 是指向上一个 link 的指针， next 指向下一个 link
	bool isDel = 0; //isDel 设置的目的是为了在析构函数中使用，默认为0
					//function
	link(int n_loop_num = 1, T n_info = 0, link *n_prev = 0, link *n_next = 0);

	~link();

	link<T> &operator=(link<T> &Link);

	link<T> *create_loop(int num);
};

template <typename T>
link<T> *link<T>::create_loop(int num)
{//创建一个循环链表并定位到第一个链结上
	if (num < 2)
	{
		cerr << "Error" << endl;
		return this;
	}
	loop_num = num;
	link<T> *temp_1 = new link<T>(num), *temp_2 = 0;
	temp_1->prev = this;
	this->next = temp_1;
	for (int i = 0; i < num - 2; ++i)
	{
		temp_2 = new link<T>(num);
		temp_1->next = temp_2;
		temp_2->prev = temp_1;
		temp_1 = temp_2;
	}
	temp_1->next = this;
	this->prev = temp_1;
	return this;
}

template <typename T>
link<T>::~link()
{//析构函数可以一次将 loop 中的所有 links 全部析构。
	if (isDel == 0)
	{
		isDel = 1;
		delete next;
	}
	else {
		//     cerr << "Destruction Success" << endl;
	}
	return;
}

template <typename T>
link<T> &link<T>::operator=(link<T> &Link)
{//这是一个深层复制构造函数
	create_loop(Link.loop_num);
	link<T> *temp = this;
	link<T> *ini = &Link;
	for (int i = 0; i < loop_num; ++i)
	{
		temp->info = ini->info;
		ini = ini->next;
		temp = temp->next;
	}
}

template <typename T>
link<T>::link(int n_loop_num, T n_info, link *n_prev, link *n_next)
{//构造函数
	info = n_info;
	prev = n_prev;
	next = n_next;
	loop_num = n_loop_num;
	//   cerr << "Construction success" << endl;
}


template <typename T>
struct queue
{
	//data
	link<T> *f, *r;
	size_t Max;
	size_t n;
	//function
	queue<T>(int n_Max)
	{
		Max = n_Max + 1;
		r = new link<T>();
		r->create_loop(Max);
		f = r;
		n = 0;
	}

	bool isEmpty()
	{
		return r == f;
	}

	bool Enter(T data)
	{
		if (r->next == f)
			return false;
		f = f->prev;
		f->info = data;
		++n;
		return true;
	}

	bool Kick()
	{
		if (isEmpty())
			return false;

		r = r->prev;
		--n;
		return true;
	}

	T &info()
	{
		assert(!isEmpty());
		return r->prev->info;
	}

	~queue<T>()
	{
		delete r;
	}

	queue<T> &operator=(queue<T> &Q)
	{
		Max = Q.Max;
		f = new link<T>;
		*f = *Q.f;
		r = f;
		for (int i = 0; i < Q.n; ++i)
			r = r->next;
		return Q;
	}
};

int main()
{
    return 0;
}

