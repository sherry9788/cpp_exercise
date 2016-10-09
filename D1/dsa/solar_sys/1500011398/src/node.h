#ifndef NODE
#define NODE

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <map>
#include <climits>
#include <ctime>

// a node structure
 template <typename T>
struct Node {
	// information
	T info;
	// the pointer of the next element
	Node *next;

	// constructor
	Node(T x, Node *n_next);
};

 template <typename T>
Node<T>::Node(T x, Node *n_next) {
	info = x;
	next = n_next;
}

#endif NODE