/*
*     �ع�� ����ѧԺ 1500011398
*     �����������������ࣨһ��ѭ��һ����ѭ������һ��ջ�࣬һ�����У�
* һ���������ࡣ������������ʵ�֡�
*     ���� create_bintree �������� vector ���飬����һ����������ָ�룬
* �����ǽ����ȸ����кͶԳ��������У�����һ����������
*     ������κ��������� bintree �ĳ�Ա���� Root_Thi �У����ĸ߶ȡ�Ҷ
* ������������ bintree �ĳ�Ա���� depth �� n_descendant �С�
*     ��ȡ�ȸ����κͶԳ��������еķ�ʽ���� data.txt ���������У�main
* �������ȡ���������д�� vector �����С�Ŀǰֻ֧�����ͱ�����
*     main ��������� data �ļ����������������У���������ĸ߶Ⱥ�
* Ҷ��������
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// link �������࣬��ѭ��˫����
template <typename T> class link {
public:
	//data
	T info; //info ��ѭ������Ĵ�����Ϣ��д����ģ���෽����ʹ�ù����и�����������
	int loop_num; //loop_num �����ѭ���������������Ĭ��Ϊ1
	link *prev, *next;  //prev ��ָ����һ�� link ��ָ�룬 next ָ����һ�� link
	bool isDel = 0; //isDel ���õ�Ŀ����Ϊ��������������ʹ�ã�Ĭ��Ϊ0
					//function
	link(int n_loop_num = 1, T n_info = 0, link *n_prev = 0, link *n_next = 0)
	{//���캯��
		info = n_info;
		prev = n_prev;
		next = n_next;
		loop_num = n_loop_num;
		//   cerr << "Construction success" << endl;
	}

	~link()
	{//������������һ�ν� loop �е����� links ȫ��������
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
	{//����һ����㸴�ƹ��캯��
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
	{//����һ��ѭ��������λ����һ��������
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

	bool append(int num = 1) { // append ������������ѭ������
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

// queue ��һ�������ࡣ
template <typename T> struct queue
{
	//data
	link<T> *f, *r; //f Ϊ����ָ�룬r Ϊ��βָ�롣
	size_t Max; //Max �Ƕ�������������
	size_t n; //n ��Ŀǰ�����е�Ԫ�ظ�����
			  //function
	queue<T>(int n_Max = 64)
	{ //���캯����Ĭ�϶�������Ϊ64��
		Max = n_Max + 1;
		r = new link<T>();
		r->create_loop(Max);
		f = r;
		n = 0;
	}

	bool isEmpty()
	{ //�ж϶����Ƿ�Ϊ�գ����Ϊ�յĻ����׺Ͷ�βָ��Ӧ��ָ��ͬһλ�á�
		return r == f;
	}

	bool Enter(T data)
	{ //��Ӳ��������������Ŀ���ǰ�Ԫ��������У������ɹ��򷵻� true��
		if (r->next == f) { //������ж϶����Ƿ����������������Զ�����64���ռ䡣
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
	{ // ���Ӳ�������������ѿ��򷵻�false�����򷵻�true��
		if (isEmpty())
			return false;

		r = r->prev;
		--n;
		return true;
	}

	T &info()
	{ // ���ص�ǰ��βԪ�ص����á�
		assert(!isEmpty());
		return r->prev->info;
	}

	~queue<T>()
	{ // ������������link���Ѿ�����Ӧ������������
	  // ����r���Խ������е���������������
		delete r;
	}

	queue<T> &operator=(queue<T> &Q)
	{ // ���еĸ�ֵ��������㸴�ơ�
		Max = Q.Max;
		f = new link<T>;
		*f = *Q.f;
		r = f;
		for (int i = 0; i < Q.n; ++i)
			r = r->next;
		return Q;
	}
};

// Node ��һ��������
template <typename T> struct Node
{
	T info; // info �Ǵ洢�����ݡ�
	Node *next; // next �ǵ��������һ��Ԫ�ء�

	Node(T x, Node *n_next = nullptr)
	{ // ���캯��,Ĭ����һ��Ԫ��Ϊ��ָ�롣
		info = x;
		next = n_next;
	}
};

// Stack ��һ��ջ�ࡣ
template <typename T> struct Stack {
	Node<T> *top = nullptr; // ջ��Ԫ�ص�ָ�롣

	Stack() = default; // Ĭ�Ϲ��캯����

	bool push(T x) { // push ������ջ��ѹ��һ��Ԫ�ء�������ӳɹ��ı�־��
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

	T pop() { // pop ��һ����ջ���������س�ջ��Ԫ�ص�ֵ��
		T tmp = top->info;
		Node<T> *p = top;
		top = p->next;
		delete p;

		return tmp;
	}

	bool isEmpty() { // isEmpty ����ջΪ��ջ�ı�־��
		return top == nullptr;
	}

	T &info() { // ���ص�ǰջ��Ԫ�ص����á�
		return top->info;
	}
};

// bintree ��һ���������ࡣ
template <typename T> struct bintree
{
	//data
public:
	T m_info; // ��ǰ���ڵ�����ݡ�
	bintree *m_L = nullptr;// ��������ָ�롣
	bintree *m_R = nullptr;// ��������ָ�롣
	bintree *m_F = nullptr;// ���׵�ָ�롣
	bool ltag = false, rtag = false;
	// ��� ltag Ϊ false ����������ָ��ָ��������������ָ��
	// �Գ����ε���һ��ɨ��Ŀ�ꡣrtag ͬ��

	//function
public:
	bintree<T>() = default; // Ĭ�Ϲ��캯����
	bintree<T>(T n_info, bintree *father = nullptr) :
		m_info(n_info), m_F(father) {} // ���캯����

	~bintree<T>()
	{ // ��������һ�ο��Խ���������ȫ��������
		if (m_R != nullptr && rtag == false)
			delete m_R;

		if (m_L != nullptr && ltag == false)
			delete m_L;
	}

	bintree<T> &operator=(bintree<T> &B)
	{ // ����һ����㸴�ƺ�����
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
	{ // ɾ����������ͬʱ����������
		if (m_L == nullptr)
			return false;

		delete m_L;
		m_L = nullptr;
		return true;
	}

	bool delR()
	{ // ɾ����������ͬʱ����������
		if (m_R == nullptr)
			return false;

		delete m_R;
		m_R = nullptr;
		return false;
	}

	bintree<T> &setL(T n_info)
	{ // ����һ�������������������������á�
		delL();
		m_L = new bintree<T>(n_info, this);
		return *m_L;
	}

	bintree<T> &setR(T n_info)
	{ // ����һ�������������������������á�
		delR();
		m_R = new bintree<T>(n_info, this);
		return *m_R;
	}

	bool isFather()
	{ // ������û�и���㣬���� true�����򷵻� false��
		return m_F == nullptr;
	}

	bintree<T> &L()
	{ // ���������������á�
		assert((!(m_L == nullptr) && ltag == false));
		return *m_L;
	}

	bintree<T> &R()
	{ // ���������������á�
		assert((!(m_R == nullptr) && rtag == false));
		return *m_R;
	}

	bintree<T> &F()
	{ // ���ظ��������á�
		assert(!isFather());
		return *m_F;
	}

	T &info()
	{ // ���ؽ�����ݵ����á�
		return m_info;
	}

	void RootFir(void foo(bintree<T> *bt))
	{ // �ȸ�ɨ�躯��������һ�� void ����ָ�롣
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
	{ // �Գ�ɨ�躯��������һ�� void ����ָ�롣
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
	{ // ���ɨ�躯��������һ�� void ����ָ�롣
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
	{ // ��������������
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
	{ // ���������Գ�ɨ�躯��������һ�� void ����ָ�롣
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
	{ // ������ȵ�ɨ�躯��������һ�� void ����ָ�롣
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

// �����ȸ�ɨ�����кͶԳ�ɨ�����У����ع�������Ķ�������ָ�롣
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

	// ���ڹ��캯�������ƣ���˵Ľ����ܻᱻ������Ρ�
	// ����Ĵ�����ɾ���������õġ�
	if (ret->m_L && ret->m_L->info() == ret->info()) {
		bintree<int> *tmp = ret;
		ret = ret->m_L;
		tmp->m_L = nullptr;
		tmp->m_R = nullptr;
		delete tmp; // ���ڵ���Ҫ����������ʡ�ռ䣬��ͬ��
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

//��д�������֮ǰ���Ѿ�д����ģ����Ķ����� bintree

//�˺������ڵݹ����һ��������������һ��ָ�롣
//���������������Ҷ�ӽ�㶼�����֣��ڲ���㶼�������
bintree<string> *create_bintree(const string &s, unsigned &i) {
	bintree<string> *curr = new bintree<string>;
	bintree<string> *ret = nullptr;//ret�Ƿ��ص�ָ��
	unsigned j = 0;
	if (isdigit(s[i])) {//��������֣��Ͱ�������������
		while (isdigit(s[++j + i]));
		curr->m_info = s.substr(i, j);
		i += j;
	}
	else {//����������֣���Ȼ�������ţ��ݹ鴴��һ��������Ϊ������
		curr = create_bintree(s, ++i);
	}
	while (true) {
		//�����������洢�����
		bintree<string> *new_tree = new bintree<string>(s.substr(i++, 1));
		new_tree->m_L = curr;
		curr = new_tree;
		ret = curr;//���صĽ������������

		if (s[i] == '(')//����������ţ��ݹ����������Ϊ������
			curr->m_R = create_bintree(s, ++i);
		else {//�����s��ǰ������д��������
			curr->m_R = new bintree<string>;
			curr = curr->m_R;
			unsigned j = 0;
			while (i + j != s.size() && isdigit(s[++j + i]));
			curr->m_info = s.substr(i, j);
			i += j;
		}
		curr = ret;
		if (i == s.size())//����������һ��char���򷵻�ret
			break;

		if (s[i] == ')') {//����������ţ��򷵻�ret
			++i;
			break;
		}
	}
	return ret;
}

//����ݹ麯�������ؼ�����
double postOrder(bintree<string> *b) {
	if (!isdigit(b->m_info[0])) {
		//����������֣���ִ�еݹ�
		double b1 = postOrder(b->m_L);
		double b2 = postOrder(b->m_R);
		//�ж�����������Ͳ�����
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
		//����������������һ����Ҷ�ӣ�������ֵ���������С
		int ret = 0;
		for (unsigned i = 0; i < b->m_info.size(); ++i)
			ret = ret * 10 + b->m_info[i] - '0';
		return ret;
	}
}

//�˺�������һ��string�����ؼ�����
int cal(string s) {
	//�������forѭ����������еĳ˳�����������ţ������ֳ˳�
	//�������ȼ����ڼӼ�������1+3*4�ᱻ��дΪ1+��3*4��
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '*' || s[i] == '/') {
			char c1[] = "(";
			char c2[] = ")";
			int f = i, r = i + 1;
			int mark = 0;
			//mark������Ǿ����������ŵĸ���
			//����д����Ϊ��ʱ��˳���������ҿ�������������
			do {
				--f;
				if (s[f] == ')')
					++mark;
				if (s[f] == '(')
					--mark;
			} while (f >= 0 && (isdigit(s[f]) || mark));
			s.insert(f + 1, c1);//����'('
			mark = 0;
			do {
				++r;
				if (s[r] == '(')
					++mark;
				if (s[r] == ')')
					--mark;
			} while ((unsigned)r < s.size() && (isdigit(s[r]) || mark));
			s.insert(r, c2);//����')'
			i += 3;
		}
	}
	s += "+0";//+0����ı�����������������0��Ϊ��ȥ��һ��bug
	unsigned i = 0;
	bintree<string> *b = create_bintree(s, i);//����������
	return postOrder(b);//���㲢return���
}

int main()
{
loop:
	string s;
	//������������� s �е���ʽ�Ƿ�Ϸ��������ʽ���Ϸ����ܻ����δ������
	cin >> s;
	cerr << cal(s) << endl;
	goto loop;
	return 0;
}
