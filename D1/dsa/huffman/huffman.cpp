#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct huffman
{
	//data
public:
	T info;
	huffman<T> *L = nullptr, *R = nullptr;

	//function
public:
	huffman<T>(T n_info) :
		info(n_info) {}

	huffman<T>() = default;

	~huffman<T>()
	{
		if (L != nullptr)
			delete L;

		if (R != nullptr)
			delete R;
	}

	huffman<T> &operator=(huffman<T> &H)
	{
		info = H.info;
		if (H.L != nullptr)
		{
			L = new huffman<T>();
			*L = *H.L;
		}
		else
			L = nullptr;
		if (H.R != nullptr)
		{
			R = new huffman<T>();
			*R = *H.R;
		}
		else
			R = nullptr;
	}

	bool isLeave()
	{
		return (L == nullptr && R == nullptr);
	}

	huffman<T> *merge(huffman<T> *H)
	{
		if (H == nullptr)
			return this;
		huffman<T> *ret = new huffman<T>(info + H->info);
		ret->L = this;
		ret->R = H;
		return ret;
	}
};

template <typename T>
huffman<T> *find_min(vector<huffman<T> *> &hv)
{
	huffman<T> *ret = hv[0];
	auto tmp_iter = hv.begin();
	for (auto iter = (++hv.begin()); iter != hv.end(); ++iter)
		if ((*iter)->info < ret->info)
		{
			tmp_iter = iter;
			ret = *iter;
		}
	hv.erase(tmp_iter);
	return ret;
}

template <typename T>
huffman<T> *huffman_tree(vector<T> vec)
{
	vector<huffman<T> *> ret;
	for (int i = 0; i < vec.size(); ++i)
	{
		huffman<T> *tmp = new huffman<T>(vec[i]);
		ret.push_back(tmp);
	}
	while (ret.size() != 1)
	{
		huffman<T> *temp_1 = find_min(ret);
		huffman<T> *temp_2 = find_min(ret);
		temp_2 = temp_2->merge(temp_1);
		ret.push_back(temp_2);
	}
	return ret[0];
}

int main()
{
	vector<int> ivec{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };
	huffman<int> *test = huffman_tree(ivec);
	cerr << test->R->info << endl;
	return 0;
}
