//Node��һ����������ѭ��
 template <typename T>
struct Node
{
	T info;				//info����Ϣ
	Node *next;			//next����һ��������Ϣ

	//constructor
	Node(T x, Node *n_next);
};
