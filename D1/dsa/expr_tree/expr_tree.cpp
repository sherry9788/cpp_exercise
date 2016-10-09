/*
*     秦光辉 物理学院 1500011398
*     代码中有两个链表类（一个循环一个不循环），一个栈类，一个队列，
* 一个二叉树类。二叉树用链表实现。
*     函数 create_bintree 接受两个 vector 数组，返回一个二叉树的指针，
* 功能是接受先根序列和对称周游序列，构造一个二叉树。
*     后根周游函数定义在 bintree 的成员函数 Root_Thi 中，树的高度、叶
* 结点个数定义在 bintree 的成员函数 depth 和 n_descendant 中。
*     获取先根周游和对称周游序列的方式是在 data.txt 中输入序列，main
* 函数会读取这个函数并写入 vector 数组中。目前只支持整型变量。
*     main 函数会接受 data 文件，输出后根周游序列，并输出树的高度和
* 叶结点个数。
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// link 是链结类，是循环双链表。
template <typename T> class link {
public:
	//data
	T info; //info 是循环链表的储存信息，写成了模板类方便在使用过程中更改数据类型
	int loop_num; //loop_num 是这个循环链表的链结数，默认为1
	link *prev, *next;  //prev 是指向上一个 link 的指针， next 指向下一个 link
	bool isDel = 0; //isDel 设置的目的是为了在析构函数中使用，默认为0
					//function
	link(int n_loop_num = 1, T n_info = 0, link *n_prev = 0, link *n_next = 0)
	{//构造函数
		info = n_info;
		prev = n_prev;
		next = n_next;
		loop_num = n_loop_num;
		//   cerr << "Construction success" << endl;
	}

	~link()
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

	link<T> &operator=(link<T> &Link)
	{//这是一个深层复制构造函数
		create_loop(Link.loop_num);
		link<T> *temp = this;
		link<T> *ini = &Link;
		for (int i = 0; i < loop_num; ++i) {
			temp->info = ini->info;
			ini = ini->next;
			temp = temp->next;
		}
	}

	link<T> *create_loop(int num)
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

	bool append(int num = 1) { // append 函数可以扩充循环链表。
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
};

// queue 是一个队列类。
template <typename T> struct queue
{
	//data
	link<T> *f, *r; //f 为队首指针，r 为队尾指针。
	size_t Max; //Max 是队列最大的容量。
	size_t n; //n 是目前队列中的元素个数。
			  //function
	queue<T>(int n_Max = 64)
	{ //构造函数，默认队列容量为64。
		Max = n_Max + 1;
		r = new link<T>();
		r->create_loop(Max);
		f = r;
		n = 0;
	}

	bool isEmpty()
	{ //判断队列是否为空，如果为空的话队首和队尾指针应该指向同一位置。
		return r == f;
	}

	bool Enter(T data)
	{ //入队操作，这个操作的目的是把元素添入队列，操作成功则返回 true。
		if (r->next == f) { //这里会判断队列是否已满，如果满则会自动扩充64个空间。
			if (!r->append(64))
				return false;
			Max += 64;
		}
		f = f->prev;
		f->info = data;
		++n;
		return true;
	}

	bool Kick()
	{ // 出队操作，如果队列已空则返回false，否则返回true。
		if (isEmpty())
			return false;

		r = r->prev;
		--n;
		return true;
	}

	T &info()
	{ // 返回当前队尾元素的引用。
		assert(!isEmpty());
		return r->prev->info;
	}

	~queue<T>()
	{ // 析构函数。在link中已经有相应的析构函数，
	  // 析构r可以将队列中的所有链接析构。
		delete r;
	}

	queue<T> &operator=(queue<T> &Q)
	{ // 队列的赋值函数是深层复制。
		Max = Q.Max;
		f = new link<T>;
		*f = *Q.f;
		r = f;
		for (int i = 0; i < Q.n; ++i)
			r = r->next;
		return Q;
	}
};

// Node 是一个单链表。
template <typename T> struct Node
{
	T info; // info 是存储的数据。
	Node *next; // next 是单链表的下一个元素。

	Node(T x, Node *n_next = nullptr)
	{ // 构造函数,默认下一个元素为空指针。
		info = x;
		next = n_next;
	}
};

// Stack 是一个栈类。
template <typename T> struct Stack {
	Node<T> *top = nullptr; // 栈顶元素的指针。

	Stack() = default; // 默认构造函数。

	bool push(T x) { // push 可以在栈顶压入一个元素。返回添加成功的标志。
		Node<T> *p = new Node<T>(x, this->top);
		if (p == NULL)
		{
			cout << "Out of space" << endl;
			return false;
		}
		else
			this->top = p;

		return true;
	}

	T pop() { // pop 是一个出栈操作，返回出栈的元素的值。
		T tmp = top->info;
		Node<T> *p = top;
		top = p->next;
		delete p;

		return tmp;
	}

	bool isEmpty() { // isEmpty 返回栈为空栈的标志。
		return top == nullptr;
	}

	T &info() { // 返回当前栈顶元素的引用。
		return top->info;
	}
};

// bintree 是一个二叉树类。
template <typename T> struct bintree
{
	//data
public:
	T m_info; // 当前根节点的数据。
	bintree *m_L = nullptr;// 左子树的指针。
	bintree *m_R = nullptr;// 右子数的指针。
	bintree *m_F = nullptr;// 父亲的指针。
	bool ltag = false, rtag = false;
	// 如果 ltag 为 false ，则左子树指针指向左子树，否则指向
	// 对称周游的下一个扫描目标。rtag 同理。

	//function
public:
	bintree<T>() = default; // 默认构造函数。
	bintree<T>(T n_info, bintree *father = nullptr) :
		m_info(n_info), m_F(father) {} // 构造函数。

	~bintree<T>()
	{ // 析构函数一次可以将所有子树全部析构。
		if (m_R != nullptr && rtag == false)
			delete m_R;

		if (m_L != nullptr && ltag == false)
			delete m_L;
	}

	bintree<T> &operator=(bintree<T> &B)
	{ // 这是一个深层复制函数。
		m_info = B.m_info;
		ltag = B.ltag;
		rtag = B.rtag;
		if (B.m_R != nullptr && rtag == false)
		{
			m_R = new bintree<T>();
			*m_R = *B.m_R;
		}

		if (B.m_L != nullptr && ltag == false)
		{
			m_L = new bintree<T>();
			*m_L = *B.m_L;
		}
	}

	int depth() {
		if (!m_L && !m_R)
			return 1;
		if (m_L && m_R)
			return 1 + (m_L->depth() > m_R->depth() ?
				m_L->depth() : m_R->depth());
		if (m_L)
			return 1 + m_L->depth();
		return 1 + m_R->depth();
	}

	int n_descendant() {
		if (!m_L && !m_R)
			return 1;
		if (m_L && m_R)
			return m_L->n_descendant() + m_R->n_descendant();
		if (m_L)
			return m_L->n_descendant();
		return m_R->n_descendant();
	}


	bool delL()
	{ // 删除左子树，同时把它析构。
		if (m_L == nullptr)
			return false;

		delete m_L;
		m_L = nullptr;
		return true;
	}

	bool delR()
	{ // 删除右子树，同时把它析构。
		if (m_R == nullptr)
			return false;

		delete m_R;
		m_R = nullptr;
		return false;
	}

	bintree<T> &setL(T n_info)
	{ // 创建一个左子树，返回左子树的引用。
		delL();
		m_L = new bintree<T>(n_info, this);
		return *m_L;
	}

	bintree<T> &setR(T n_info)
	{ // 创建一个右子树，返回右子树的引用。
		delR();
		m_R = new bintree<T>(n_info, this);
		return *m_R;
	}

	bool isFather()
	{ // 如果结点没有父结点，返回 true，否则返回 false。
		return m_F == nullptr;
	}

	bintree<T> &L()
	{ // 返回左子树的引用。
		assert((!(m_L == nullptr) && ltag == false));
		return *m_L;
	}

	bintree<T> &R()
	{ // 返回右子树的引用。
		assert((!(m_R == nullptr) && rtag == false));
		return *m_R;
	}

	bintree<T> &F()
	{ // 返回父结点的引用。
		assert(!isFather());
		return *m_F;
	}

	T &info()
	{ // 返回结点数据的引用。
		return m_info;
	}

	void RootFir(void foo(bintree<T> *bt))
	{ // 先根扫描函数，接受一个 void 函数指针。
		Stack<bintree<T> *> SB;
		bintree<T> *b1;
		SB.push(this);
		while (!SB.isEmpty())
		{
			b1 = SB.info();
			SB.pop();
			if (b1 != nullptr)
			{
				foo(b1);
				SB.push(b1->m_R);
				SB.push(b1->m_L);
			}
		}
	}

	void RootSec(void foo(bintree<T> *bt))
	{ // 对称扫描函数，接受一个 void 函数指针。
		Stack<bintree<T> *> SB;
		bintree<T> *b;
		b = this;
		do
		{
			while (b != nullptr)
			{
				SB.push(b);
				b = b->m_L;
			}

			do
			{
				b = SB.pop();
				foo(b);
			} while (b->m_R == nullptr && !SB.isEmpty());

			b = b->m_R;
		} while (!SB.isEmpty() || b != nullptr);
	}

	void RootThi(void foo(bintree<T> *bt))
	{ // 后根扫描函数，接受一个 void 函数指针。
		map<bintree<T> *, int> BM;
		Stack<bintree<T> *> SB;
		bintree<T> *b;
		SB.push(this);
		while (!SB.isEmpty())
		{
			b = SB.pop();
			if (BM[b] == 0)
			{
				++BM[b];
				SB.push(b);
				if (b->m_L != nullptr)
					SB.push(b->m_L);
			}
			else if (BM[b] == 1)
			{
				++BM[b];
				SB.push(b);
				if (b->m_R != nullptr)
					SB.push(b->m_R);
			}
			else
				foo(b);
		}
	}

	void threadRootSec()
	{ // 线索化二叉树。
		Stack<bintree<T> *> SB;
		bintree<T> *b, *pr = nullptr;
		b = this;
		do
		{
			while (b != nullptr)
			{
				SB.push(b);
				b = b->m_L;
			}

			do
			{
				b = SB.pop();
				if (pr != nullptr && pr->m_R == nullptr)
				{
					pr->m_R = b;
					pr->rtag = true;
				}
				if (b->m_L == nullptr)
				{
					b->m_L = pr;
					b->ltag = true;
				}
				pr = b;

			} while (b->m_R == nullptr && b->rtag == false && !SB.isEmpty());
			if (b->rtag == true)
				b = nullptr;
			else
				b = b->m_R;
		} while (!SB.isEmpty() || b != nullptr);
	}

	void inorderRootSec(void foo(bintree<T> *))
	{ // 按照线索对称扫描函数，接受一个 void 函数指针。
		bintree<T> *b;
		b = this;
		while (b->m_L != 0)
			b = b->m_L;
		while (true)
		{
			foo(b);
			if (b->rtag == true)
				b = b->m_R;
			else if (b->m_R != nullptr)
			{
				b = b->m_R;
				while (b->ltag != true)
					b = b->m_L;
			}
			else
				break;
		}
	}

	void levelOrder(void foo(bintree<T> *bt))
	{ // 广度优先的扫描函数，接受一个 void 函数指针。
		queue<bintree *> QB;
		QB.Enter(this);
		bintree *b;
		do
		{
			b = QB.info();
			QB.Kick();
			foo(b);
			if (b->m_L != nullptr)
				QB.Enter(b->m_L);
			if (b->m_R != nullptr)
				QB.Enter(b->m_R);
		} while (!QB.isEmpty());
	}
};

// 接受先根扫描序列和对称扫描序列，返回构造出来的二叉树的指针。
bintree<int> *create_bintree(vector<int> f, vector<int> s) {
	assert(f.size() == s.size() && f.size() != 0);
	bintree<int> *ret = new bintree<int>(f[0]);
	if (f.size() == 1)
		return ret;
	bintree<int> *curr = ret;
	queue<int> q_f(100), q_s(100);
	for (auto c : f)
		q_f.Enter(c);
	for (auto c : s)
		q_s.Enter(c);
	Stack<bintree<int> *> Stack_tree;
	Stack_tree.push(curr);
	while (!q_f.isEmpty()) {
		while (!q_f.isEmpty() && Stack_tree.info()->info() != q_s.info()) {
			if (q_f.info() == f[0]) {
				q_f.Kick();
			}
			curr->setL(q_f.info());
			q_f.Kick();
			curr = curr->m_L;
			Stack_tree.push(curr);
		}

		while (!q_f.isEmpty() && !Stack_tree.isEmpty()
			&& Stack_tree.info()->info() == q_s.info()) {
			q_s.Kick();
			curr = Stack_tree.pop();
		}

		if (!q_f.isEmpty()) {
			curr->setR(q_f.info());
			curr = curr->m_R;
			Stack_tree.push(curr);
			q_f.Kick();
		}
	}

	// 由于构造函数的限制，最顶端的结点可能会被添加两次。
	// 下面的代码是删除这个结点用的。
	if (ret->m_L && ret->m_L->info() == ret->info()) {
		bintree<int> *tmp = ret;
		ret = ret->m_L;
		tmp->m_L = nullptr;
		tmp->m_R = nullptr;
		delete tmp; // 根节点需要被析构，节省空间，下同。
	}
	else if (ret->m_R && ret->m_R->info() == ret->info()) {
		bintree<int> *tmp = ret;
		ret = ret->m_R;
		ret->m_R = ret->m_L;
		ret->m_L = nullptr;
		tmp->m_L = nullptr;
		tmp->m_R = nullptr;
		delete tmp;
	}
	return ret;
}

template <typename T>
void print(bintree<T> *b) {
	cerr << b->info() << " ";
}

//在写这个函数之前我已经写好了模板类的二叉树 bintree

//此函数用于递归产生一个二叉树，返回一个指针。
//这个二叉树中所有叶子结点都是数字，内部结点都是运算符
bintree<string> *create_bintree(const string &s, unsigned &i) {
	bintree<string> *curr = new bintree<string>;
	bintree<string> *ret = nullptr;//ret是返回的指针
	unsigned j = 0;
	if (isdigit(s[i])) {//如果是数字，就把它当作左子树
		while (isdigit(s[++j + i]));
		curr->m_info = s.substr(i, j);
		i += j;
	}
	else {//如果不是数字，必然是左括号，递归创建一个新树作为左子树
		curr = create_bintree(s, ++i);
	}
	while (true) {
		//这个结点用来存储运算符
		bintree<string> *new_tree = new bintree<string>(s.substr(i++, 1));
		new_tree->m_L = curr;
		curr = new_tree;
		ret = curr;//返回的结点是运算符结点

		if (s[i] == '(')//如果是左括号，递归产生新树作为右子树
			curr->m_R = create_bintree(s, ++i);
		else {//否则把s当前的数字写入右子树
			curr->m_R = new bintree<string>;
			curr = curr->m_R;
			unsigned j = 0;
			while (i + j != s.size() && isdigit(s[++j + i]));
			curr->m_info = s.substr(i, j);
			i += j;
		}
		curr = ret;
		if (i == s.size())//如果到了最后一个char，则返回ret
			break;

		if (s[i] == ')') {//如果是右括号，则返回ret
			++i;
			break;
		}
	}
	return ret;
}

//后序递归函数，返回计算结果
double postOrder(bintree<string> *b) {
	if (!isdigit(b->m_info[0])) {
		//如果不是数字，就执行递归
		double b1 = postOrder(b->m_L);
		double b2 = postOrder(b->m_R);
		//判断运算符的类型并运算
		if (b->m_info[0] == '+')
			return b1 + b2;
		else if (b->m_info[0] == '-')
			return b1 - b2;
		else if (b->m_info[0] == '*')
			return b1 * b2;
		else
			return b1 / b2;
	}
	else {
		//如果不是运算符，则一定是叶子，计算其值，返回其大小
		int ret = 0;
		for (unsigned i = 0; i < b->m_info.size(); ++i)
			ret = ret * 10 + b->m_info[i] - '0';
		return ret;
	}
}

//此函数接受一个string，返回计算结果
int cal(string s) {
	//下面这个for循环负责给所有的乘除运算符加括号，来体现乘除
	//运算优先级高于加减，例如1+3*4会被改写为1+（3*4）
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '*' || s[i] == '/') {
			char c1[] = "(";
			char c2[] = ")";
			int f = i, r = i + 1;
			int mark = 0;
			//mark用来标记经历过的括号的个数
			//这样写是因为有时候乘除运算符左右可能正好是括号
			do {
				--f;
				if (s[f] == ')')
					++mark;
				if (s[f] == '(')
					--mark;
			} while (f >= 0 && (isdigit(s[f]) || mark));
			s.insert(f + 1, c1);//插入'('
			mark = 0;
			do {
				++r;
				if (s[r] == '(')
					++mark;
				if (s[r] == ')')
					--mark;
			} while ((unsigned)r < s.size() && (isdigit(s[r]) || mark));
			s.insert(r, c2);//插入')'
			i += 3;
		}
	}
	s += "+0";//+0不会改变程序运算结果，这里加0是为了去掉一个bug
	unsigned i = 0;
	bintree<string> *b = create_bintree(s, i);//产生二叉树
	return postOrder(b);//运算并return结果
}

int main()
{
loop:
	string s;
	//函数不负责检验 s 中的算式是否合法，如果算式不合法可能会产生未定义结果
	cin >> s;
	cerr << cal(s) << endl;
	goto loop;
	return 0;
}
