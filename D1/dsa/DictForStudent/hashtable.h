#ifndef HASH
#define HASH

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "element.h"

using namespace std;

//HashTable是哈希表的类
 template <typename K, typename V>
struct HashTable
{
	//data
public:
	int m = 0;						//哈希表的容量
	int n_collision = 0;			//碰撞次数
	vector<int> position_collision; //碰撞位置
	element<K, V> *ele = nullptr;	//存储元素的数组

	//function
public:
	//default constructor
	HashTable() = default;

	//constructor
	HashTable(int n_m);

	//destructor
	~HashTable();

	//copy constructor
	HashTable(HashTable &H);

	//assignment
	HashTable &operator=(HashTable &H);

	//检索函数
	V operator[](K n_key);

	//delete function
	V del(K n_key);
	
	//hash function
	int h(K n_key);

	//线性搜索函数
	bool linear_search(K n_key, int &pos);
	
	//插入函数
	void insert(K n_key, V n_value);

	//插入函数
	void insert(element<K, V> n_ele);
};

 template <typename K, typename V>
HashTable<K, V>::HashTable(int n_m) {
	m = n_m;
	ele = new element<K, V>[m];
	//如果没有生成数组，就结束程序
	assert(ele);
	//将数组中的所有元素关键码置空
	for (int i = 0; i < m; ++i)
		ele[i] = element<K, V>();
}

 template <typename K, typename V>
HashTable<K, V>::~HashTable() {
	delete []ele;
}

 template <typename K, typename V>
HashTable<K, V>::HashTable(HashTable &H) {
	m = H.m;
	n_collision = H.n_collision;
	for (int i = 0; i < m; ++i)
		ele[i] = H.ele[i];
}

 template <typename K, typename V>
HashTable<K, V> &HashTable<K, V>::operator=(HashTable &H) {
	if (ele)
		delete []ele;
	m = H.m;
	n_collision = H.n_collision;
	for (int i = 0; i < m; ++i)
		ele[i] = H.ele[i];
	return *this;
}

 template <typename K, typename V>
V HashTable<K, V>::operator[](K n_key) {
	int index = h(n_key);
	//用ini记录最初确定的哈希值
	int ini = index;		
	if (ele[index].key == n_key)
		//如果已经找到元素，直接返回
		return ele[index].value;
	//否则按顺序找，知道找到或者回到原来的哈希值位置
	for (++index; index != ini; ++index) {
		index %= m;
		if (ele[index].key == n_key)
			return ele[index].value;
	}
	//如果没有找到，就创建一个临时变量并返回
	cerr << "Not Found";
	return V();
}

 template <typename K, typename V>
int HashTable<K, V>::h(K n_key) {
	//哈希值的算法是把string中前两个汉字对应的四个char找出来，相加并模容量的大小
	return ((int)(unsigned char)n_key[0] + (int)(unsigned char)n_key[1] 
		+ (int)(unsigned char)n_key[2] + (int)(unsigned char)n_key[3]) % m;
}

 template <typename K, typename V>
bool HashTable<K, V>::linear_search(K n_key, int &pos) {
	int index = h(n_key);
	int ini = index;
	if (ele[index].key == V()) {
		pos = index;
		return true;
	}
	//如果发生了碰撞，碰撞记录器要加一
	++n_collision;
	//同时要记录下碰撞的位置
	position_collision.push_back(pos);
	//找下一个空位置
	for (++index; index != ini; ++index) {
		index %= m;
		if (ele[index].key == V()) {
			pos = index;
			return true;
		}
	}
	//没有找到说明哈希表已满，返回false
	return false;
}

 template <typename K, typename V>
void HashTable<K, V>::insert(K n_key, V n_value) {
	int pos;
	//如果哈希表已满，直接终止程序
	assert(linear_search(n_key, pos));
	ele[pos].key = n_key;
	ele[pos].value = n_value;
}

template <typename K, typename V>
void HashTable<K, V>::insert(element<K, V> n_ele) {
	insert(n_ele.key, n_ele.value);
}
 
 template <typename K, typename V>
V HashTable<K, V>::del(K n_key) {
	//ret记录返回删除的元素的值
	V ret;
	int index = h(n_key);
	int ini = index;
	//如果已经找到，就记录该值
	if (ele[index].key == n_key)
		ret = ele[index].value;
	else {
		//如果没有找到，就递增index，一直向下寻找，直到找到为止
		for (++index; index != ini; ++index) {
			index %= m;
			if (ele[index].key == n_key)
				ret = ele[index].value;
		}
		//如果没有改元素，就直接返回一个默认构造临时变量
		if (index == ini)
			return V();
	}
	
	//space记录当前空位的伪地址
	int space = index;
	//next_space记录下一个空地址的位置
	int next_space = index + 1;
	//while循环负责定位下一个空地址
	while (ele[next_space].key != K()) {
		++next_space;
		if (next_space == m)
			next_space = 0;
	}

	//置空要删除元素的关键码
	ele[index].key = K();

	//递增伪地址
	++index;
	//如果循环就置0
	if (index == m)
		index = 0;
	
	if(next_space < index)
		//发生循环的情况
		while (index != next_space) {
			if (h(ele[index].key) < space) {
				//如果当前元素不能被检索到
				ele[space].key = ele[index].key;
				ele[space].value = ele[index].value;
				//移动空位
				space = index;
			}
			++index;
			//循环则置0
			if (index == m)
				index = 0;
		}
	else
		//未发生循环的情况
		while (index != next_space) {
			if (h(ele[index].key) < space || h(ele[index].key) > next_space) {
				//如果当前元素不能被检索到
				ele[space].key = ele[index].key;
				ele[space].value = ele[index].value;
				//移动空位
				space = index;
			}
			++index;
		}
	
	return ret;
}

#endif