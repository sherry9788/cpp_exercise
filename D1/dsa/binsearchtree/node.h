//Node是一个单链表，不循环
 template <typename T>
struct Node
{
	T info;				//info是信息
	Node *next;			//next是下一个结点的信息

	//constructor
	Node(T x, Node *n_next);
};
