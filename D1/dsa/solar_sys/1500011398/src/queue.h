#ifndef QUEUE
#define QUEUE

#include "link.h"

 template <typename T>
struct queue {
public:
	// function
	// constructor
	queue<T>(int n_Max);

	// assignment function
	queue<T> &operator=(queue<T> &Q);

	// return whether the queue is empty
	bool isEmpty();

	// add a data in the rear
	bool Enter(T data);

	// kick a data in the head
	bool Kick();

	// return the value of the data on the head
	T &info();

	// destructor
	~queue<T>();

private:
	// data
	// the pointer of the front and the rear
	link<T> *f, *r;
	
	// the capacity of the queue
	int Max;

	// the number of the current datas
	int n;
};

 template <typename T>
queue<T>::queue(int n_Max) {
	// Max need to be more than n_Max by 1
	Max = (int)n_Max + 1;
	r = new link<T>();
	r->create_loop(Max);
	f = r;
	n = 0;
}

 template <typename T>
bool queue<T>::isEmpty() {
	// if the rear and the front meet
	// the queue is empty
	return r == f;
}

 template <typename T>
bool queue<T>::Enter(T data) {
	if (r->next == f)
		// it means that the queue is full
		return false;
	f = f->prev;
	f->info = data;
	++n;
	return true;
}

 template <typename T>
bool queue<T>::Kick() {
	if (isEmpty())
		return false;

	r = r->prev;
	--n;
	return true;
}

 template <typename T>
T &queue<T>::info() {
	assert(!isEmpty());
	return r->prev->info;
}

 template <typename T>
queue<T>::~queue() {
	// this function can free all spaces that the link loop
	// allocated
	delete r;
}

 template <typename T>
queue<T> &queue<T>::operator=(queue<T> &Q) {
	// deep copy
	Max = Q.Max;
	f = new link<T>;
	*f = *Q.f;
	r = f;
	for (int i = 0; i < Q.n; ++i)
		r = r->next;
	return Q;
}

#endif