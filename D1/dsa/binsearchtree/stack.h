#include "node.h"

//Stack是一个栈
 template <typename T>
struct Stack
{
	Node<T> *top;		//栈顶元素

	//constructor
	Stack();			

	//在栈顶加入元素
	bool push(T x);
	
	//出栈并返回其值
	T pop();

	//判断栈是否为空
	bool isEmpty();

	//返回栈顶元素的引用
	T &info();
};
