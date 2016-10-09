#include <iostream>
#include <cstdlib>
#include <ctime>

#define PRINT

using namespace std;

template <typename T>
struct seq
{
	int Max = 2147483647;
	int n;
	T *data;

	bool createSeq(int n_n)
	{
		n = n_n;
		data = new T[n];
		for (int i = 0; i < n; ++i)
			data[i] = i + 1;
		return true;
	}

	seq()
	{
		data = nullptr;
		n = 0;
	}

	bool del(int m)
	{
		if (m < 0 || m > n)
			return false;

		for (int i = m; i < n - 1; ++i)
		{
			data[i] = data[i + 1];

		}
		--n;
		return true;
	}

	bool isEmpty()
	{
		return n == 0;
	}

};

template <typename T> class link
{
public:
	//data
	T info; //info ��ѭ������Ĵ�����Ϣ��д����ģ���෽����ʹ�ù����и�����������
	int loop_num; //loop_num �����ѭ���������������Ĭ��Ϊ1
	link *prev, *next;  //prev ��ָ����һ�� link ��ָ�룬 next ָ����һ�� link
	bool isDel = 0; //isDel ���õ�Ŀ����Ϊ��������������ʹ�ã�Ĭ��Ϊ0
					//function
	link(int n_loop_num = 1, T n_info = 0, link *n_prev = 0, link *n_next = 0);

	~link();

	link<T> operator=(link<T> Link);

	link<T> *operator[](int seq);

	link<T> *deleteLink();
	link<T> *insertLink(link<T> *Ins);
	link<T> *appendLink(link<T> *App);

	link<T> *create_loop(int num);
	link<T> *SetInfo();
};

template <typename T>
link<T>::~link()
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

template <typename T>
link<T> link<T>::operator=(link<T> Link)
{//����һ��ǳ�㸴�ƹ��캯��
	info = Link.info;
	prev = Link.prev;
	next = Link.next;
	loop_num = Link.loop_num;
}

template <typename T>
link<T> *link<T>::operator[](int seq)
{//ʹ��[]����λ link
	link *temp = this;
	if (seq >= 0)
		for (int i = 0; i < seq - 1; ++i)
		{
			temp = temp->next;
		}
	else
		for (int i = 0; i < -seq; ++i)
		{
			temp = temp->prev;
		}
	return temp;
}

template <typename T>
link<T>::link(int n_loop_num, T n_info, link *n_prev, link *n_next)
{//���캯��
	info = n_info;
	prev = n_prev;
	next = n_next;
	loop_num = n_loop_num;
	//   cerr << "Construction success" << endl;
}

template <typename T>
link<T> *link<T>::deleteLink()
{//ɾȥһ�� link ����λ����һ�� link
	this->next->prev = this->prev;
	this->prev->next = this->next;
	return this->next;
}

template <typename T>
link<T> *link<T>::insertLink(link *Ins)
{//������ link��֮ǰ����һ��������롡����λ������ġ������
	Ins->next = this;
	Ins->prev = this->prev;
	this->prev->next = Ins;
	this->next->prev = Ins;
	return Ins;
}

template <typename T>
link<T> *link<T>::appendLink(link *App)
{//������ link ֮�����һ�� link ����λ��ԭ���� link ��
	App->prev = this;
	App->next = this->next;
	this->next->prev = App;
	this->next = App;
	return this;
}

template <typename T>
link<T> *link<T>::create_loop(int num)
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

template <typename T>
link<T> *link<T>::SetInfo()
{//����˳��� link ��ֵ����λ����һ��������
	link *Link = this;
	for (int i = 0; i < this->loop_num; ++i)
	{
		Link->info = i + 1;
		Link = Link->next;
	}
	return this;
}

int main() {
	return 0;
}