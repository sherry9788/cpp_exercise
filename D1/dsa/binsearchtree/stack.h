#include "node.h"

//Stack��һ��ջ
 template <typename T>
struct Stack
{
	Node<T> *top;		//ջ��Ԫ��

	//constructor
	Stack();			

	//��ջ������Ԫ��
	bool push(T x);
	
	//��ջ��������ֵ
	T pop();

	//�ж�ջ�Ƿ�Ϊ��
	bool isEmpty();

	//����ջ��Ԫ�ص�����
	T &info();
};
