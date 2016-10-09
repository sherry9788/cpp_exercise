#include "node.h"

template <typename T>
Node<T>::Node(T x, Node *n_next)
{
	info = x;
	next = n_next;
}
