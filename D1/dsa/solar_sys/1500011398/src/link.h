#ifndef LINK
#define LINK

#include <iostream>
#include <cassert>

template <typename T>
class link
{
public:
	// function
	// constructor
	link(int n_loop_num = 1, T n_info = 0, link *n_prev = 0, link *n_next = 0);

	// destructor
	~link();

	// assignment function
	link<T> &operator=(link<T> &Link);

	// create a link loop that contains num links
	// return the pointer of the first link
	link<T> *create_loop(int num);

	bool append(int num);

public:
	// data
	// information
	T info;
	// the number of the links of the loop
	int loop_num;

	bool isDel = false;

	// pointer of the previous link ande the next link
	link *prev, *next;
};

template <typename T>
link<T> *link<T>::create_loop(int num) {
	if (num < 2) {
		// the num couldn't be less than 2
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
link<T>::~link() {
	// destructor can free all spaces that the loop
	// allocated
	if (isDel)
		return;
	link<T> *ptr = next;
	vector<link<T> *> del_vec;
	while (ptr != this) {
		ptr->isDel = true;
		del_vec.push_back(ptr);
		ptr = ptr->next;
	}
	for (auto c : del_vec)
		delete c;
}

template <typename T>
link<T> &link<T>::operator=(link<T> &Link) {
	// deep copy
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
link<T>::link(int n_loop_num, T n_info, link *n_prev, link *n_next) {
	info = n_info;
	prev = n_prev;
	next = n_next;
	loop_num = n_loop_num;
	isDel = false;
}

template <typename T>
bool link<T>::append(int num = 1) {
	assert(num > 0);
	link<T> *new_link = new link<T>;
	if (!new_link)
		return false;
	new_link->create_loop(num);
	next->prev = new_link->prev;
	new_link->prev->next = next;
	next = new_link;
	new_link->prev = this;
	auto tmp = next;
	int new_loop_num = loop_num + num;
	while (tmp != this) {
		tmp->loop_num = new_loop_num;
		tmp = tmp->next;
	}
	return true;
}

#endif