#ifndef STACK
#define STACK

// a stack structure
 template <typename T>
struct Stack {
	// the pointer
	Node<T> *top;

	// constructor
	Stack();

	// add a element
	bool push(T x);

	// delete a element and return its value
	T pop();

	// return whether it is empty
	bool isEmpty();

	// return the first value of the stack
	T &info();
};

 template <typename T>
T &Stack<T>::info() {
	return top->info;
}

 template <typename T>
Stack<T>::Stack() {
	this->top = nullptr;
}

 template <typename T>
bool Stack<T>::isEmpty() {
	return top == nullptr;
}

 template <typename T>
bool Stack<T>::push(T x) {
	Node<T> *p = new Node<T>(x, this->top);
	if (p == NULL) {
		cout << "Out of space" << endl;
		return false;
	}
	else
		this->top = p;

	return true;
}

 template <typename T>
T Stack<T>::pop() {
	T tmp = top->info;
	Node<T> *p = top;
	top = p->next;
	delete p;

	return tmp;
}

#endif