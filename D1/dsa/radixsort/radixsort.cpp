#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <ctime>
#include <fstream>

using namespace std;

inline int loc(int num, int index, int step = 10) {
	if (index == 1)
		return num % step;
	else
		return loc(num / step, index - 1, step);
}

template <typename T> class link
{
public:
	//data
	T info; //info 是循环链表的储存信息，写成了模板类方便在使用过程中更改数据类型
	int loop_num; //loop_num 是这个循环链表的链结数，默认为1
	link *prev, *next;  //prev 是指向上一个 link 的指针， next 指向下一个 link
	bool isDel = 0; //isDel 设置的目的是为了在析构函数中使用，默认为0
					//function
	link() = default;

	link(int n_loop_num, T n_info = T(), link *n_prev = 0, link *n_next = 0)
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
			//         cerr << "Destruction Success" << endl;
		}
		return;
	}

	link<T> &operator=(link<T> &Link)
	{//这是一个深层复制构造函数
		create_loop(Link.loop_num);
		link<T> *temp = this;
		link<T> *ini = &Link;
		for (int i = 0; i < loop_num; ++i)
		{
			temp->info = ini->info;
			ini = ini->next;
			temp = temp->next;
		}
		return *this;
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

	link<T>(const link<T> &CL)
	{
		CL = *this;
	}

	bool append() {
		link<T> *append_link = new link<T>();
		if (!append_link) {
			cerr << "Out of space" << endl;
			return false;
		}
		append_link->loop_num = loop_num;
		append_link->isDel = 0;
		append_link->prev = this;
		append_link->next = this->next;
		append_link->prev->next = append_link;
		append_link->next->prev = append_link;
		return true;
	}
};

template <typename T>
struct queue
{
	//data
	link<T> *f, *r;
	size_t Max;
	size_t n;
	//function
	queue<T>()
	{
		Max = 1000;
		r = new link<T>();
		r->create_loop(Max);
		f = r;
		n = 0;
	}

	bool isEmpty()
	{
		return r == f;
	}

	bool Enter(const T &data)
	{
		if (r->next == f) {
			int new_loop_num = r->loop_num + 100;
			auto ptr = r;
			for (; ptr != r; ptr = ptr->next)
				ptr->loop_num = new_loop_num;
			for (int i = 0; i < 100; ++i) {
				//      if(!ptr->append())
				return false;
			}
			Max += 100;
		}
		f = f->prev;
		f->info = data;
		++n;
		return true;
	}

	T Kick()
	{
		assert(!isEmpty());
		T ret = info();

		r = r->prev;
		--n;
		return ret;
	}

	T &info()
	{
		assert(!isEmpty());
		return r->prev->info;
	}

	~queue<T>()
	{
		delete r;
	}

	queue<T> &operator=(queue<T> &Q)
	{
		delete r;
		Max = Q.Max;
		f = new link<T>;
		*f = *Q.f;
		r = f;
		for (int i = 0; i < Q.n; ++i)
			r = r->next;
		return Q;
	}

	queue<T>(const queue<T> &Q)
	{
		Max = Q.Max;
		f = new link<T>;
		*f = *Q.f;
		r = f;
		for (int i = 0; i < Q.n; ++i)
			r = r->next;
	}
};

void radixsort(vector<int> &vec, int step = 10) {
	int n = 0;
	for (auto c : vec)
		if (c > n)
			n = c;
	int num = 1, index_max = 2;
	while (n > num * step - 1) {
		num *= step;
		++index_max;
	}
	queue<int> *q = new queue<int>[step]();
	for (int index = 1; index < index_max; ++index) {
		for (auto c : vec)
			q[loc(c, index, step)].Enter(c);
		int k = 0;
		for (int i = 0; i < step; ++i)
			while (!q[i].isEmpty())
				vec[k++] = q[i].Kick();
	}
	delete[]q;
}

void bin_radixsort(vector<int> &vec) {
	int n = 0;
	for (auto c : vec)
		if (c > n)
			n = c;
	int num = 1, index_max = 2;
	while (n > num * 2 - 1) {
		num *= 2;
		++index_max;
	}
	queue<int> *q = new queue<int>[2]();
	int loc = 1;
	for (int index = 1; index < index_max; ++index) {
		for (auto c : vec)
			q[(c & loc) != 0].Enter(c);
		int k = 0;
		while (!q[0].isEmpty())
			vec[k++] = q[0].Kick();
		while (!q[1].isEmpty())
			vec[k++] = q[1].Kick();
		loc <<= 1;
	}
	delete[]q;
}

void print(const vector<int> &vec) {
	for (auto c : vec)
		cerr << c << " ";
	cerr << endl;
}

int main() {
	ofstream out("log.dat", ofstream::app);
	int n;
	cin >> n;
	vector<int> vec;
	while (--n != 0)
		vec.push_back(rand());
	for (int x = 2; x < 1000; ++x) {
		out << "x = " << x << " ";
		double t = clock();
		vector<int> V = vec;
		radixsort(V, x);
		out << clock() - t << endl;
	}
	return 0;
}
