#ifndef DICT
#define DICT

#include <vector>

//element类是存储每个字典元素的类
#include "element.h"
//quick是快速排序的函数
#include "quicksort.h"

 template <typename K, typename V>
struct dict
{
	//data
	element<K, V> *Dic;		//字典元素定义在一个数组中
	size_t Max;				//Max是字典的最大容量
	size_t n;				//n是字典的当前元素数量

	//function

	//constructor
	dict<K, V>(size_t n_Max = INT_MAX); 
	
	//destructor
	~dict();

	//assignment function
	dict &operator=(const dict &D);

	//排序函数
	void sort();

	//插入函数，插入函数不负责排序
	dict<K, V> &insert(const K &key, const V &value);

	//打印字典中的所有元素
	dict<K, V> &print();

	//[]中放入key，可以快速检索到对应value
	V operator[](K key);
};

 template <typename K, typename V>
void dict<K, V>::sort() {
	//因为快速排序算法使用的是vector数组，所以先转换ele
	vector<element<K, V> > ele_vec;

	for (unsigned i = 0; i < n; ++i) 
		ele_vec.push_back(Dic[i]);

	//快速排序函数
	quicksort(ele_vec);

	//vector已经排好序，将其中的元素依次放回原数组中
	for (unsigned i = 0; i < n; ++i)
		Dic[i] = ele_vec[i];
}

 template <typename K, typename V>
dict<K, V>::dict(size_t n_Max = INT_MAX){
	Max = n_Max;
	n = 0;
	Dic = new element<K, V>[Max];
}

 template <typename K, typename V>
dict<K, V>::~dict() {
	if(Dic)
		delete []Dic;
}

 template <typename K, typename V>
dict<K, V> &dict<K, V>::operator=(const dict &D) {
	Max = D.Max;
	n = D.n;
	for (int i = 0; i < n; ++i)
		Dic[i] = D.Dic[i];
	return *this;
}

 template <typename K, typename V>
dict<K, V> &dict<K, V>::insert(const K &key, const V &value) {
	Dic[n] = element<K, V>(key, value);
	++n;								 //计数器递增
	return *this;
}

 template <typename K, typename V>
dict<K, V> &dict<K, V>::print() {
	for (unsigned i = 0; i < n; ++i)
		cerr << Dic[i].key << " " << Dic[i].value << endl;
	return *this;
}

 template <typename K, typename V>
V dict<K, V>::operator[](K key){
	//检索函数使用了二分搜索
	int n1 = 0, n2 = n;
	while (n1 != n2) {
		int mid = (n1 + n2) / 2;
		if (mid == n1 || mid == n2)
			break;
		if (Dic[mid].key > key)
			n2 = mid;
		else if (Dic[mid].key < key)
			n1 = mid;
		else
			return Dic[mid].value;
	}
	//如果没有检索到，就创建一个默认构造的临时变量并返回
	return V();
}

#endif