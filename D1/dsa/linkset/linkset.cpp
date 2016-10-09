#include <iostream>

using namespace std;

template <typename T>
struct linkset
{
	//data
public:
	linkset *next;
	linkset *prev;
	T info;
	bool del = false;

	//function
public:
	linkset<T>()
	{
		next = nullptr;
		prev = nullptr;
	}

	linkset<T>(T n_info, linkset *n_next, linkset *n_prev)
	{
		info = n_info;
		next = n_next;
		prev = n_prev;
	}

	~linkset<T>()
	{
		del = true;
		if (next != nullptr && next->del == false)
			delete next;
		if (prev != nullptr && prev->del == false)
			delete prev;
	}

	linkset<T> &operator=(linkset<T> &L)
	{
		info = L.info;
		if (L.next != nullptr)
			*next = *L.next;
		else
			next = nullptr;

		if (L.prev != nullptr)
			*prev = *L.prev;
		else
			prev = nullptr;
	}

	linkset<T> &insert_ele(T n_info)
	{
		linkset<T> *temp = next, *temp_1 = this;
		while (temp != nullptr)
		{
			if (temp->info < n_info)
			{
				temp_1 = temp;
				temp = temp->next;
			}
			else
				break;
		}
		linkset<T> *Ins = new linkset<T>(n_info, temp_1->next, temp_1);
		temp_1->next = Ins;
		if (Ins->next != nullptr)
			Ins->next->prev = Ins;
		return *this;
	}

	linkset<T> &print()
	{
		linkset<T> *temp = next;
		while (temp != nullptr)
		{
			cerr << temp->info << " ";
			temp = temp->next;
		}
		cerr << endl;
		return *this;
	}

	linkset<T> *intersect(const linkset<T> &CL)
	{
		linkset<T> *ret = new linkset<T>();
		linkset<T> *tmp_1, *tmp_2;
		if (next->info < CL.next->info)
		{
			tmp_1 = next;
			tmp_2 = CL.next;
		}
		else
		{
			tmp_1 = CL.next;
			tmp_2 = next;
		}
		while (tmp_1 != nullptr && tmp_2 != nullptr)
		{
			if (tmp_1->info == tmp_2->info)
			{
				ret->insert_ele(tmp_1->info);
				tmp_1 = tmp_1->next;
				tmp_2 = tmp_2->next;
			}
			else if (tmp_1->info > tmp_2->info)
				tmp_2 = tmp_2->next;
			else
				tmp_1 = tmp_1->next;
		}
		return ret;
	}
};

int main()
{
	linkset<int> L;
	L.insert_ele(1).insert_ele(3).insert_ele(2);
	linkset<int> L1 = L;
	L1.insert_ele(-1);
	L.insert_ele(-2);
	L.print();
	L1.print();
	linkset<int> *Intsec = L1.intersect(L);
	Intsec->print();
	return 0;
}
