#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <map>

#include "stack.h"

using namespace std;

//element类用来保存每个结点的信息
template <typename K, typename V>
struct element{
	K key;
	V value;
	element(K n_key, V n_value) :
		key(n_key), value(n_value) {}
};

//计算当前结点的R值（根的位置）
int cal_r(map<vector<int>, int> &C, int i, int j, int &r);

//bintree是二叉搜索树，K为关键码，V为其值
template <typename K, typename V>
struct bintree
{
	//data
public:
	K key;								//关键码
	V value;							//保存的值
	bintree *m_L = nullptr;				//left	
	bintree *m_R = nullptr;				//rgiht
	bool isFir = true;					//记录是不是第一个被创建

	//function
public:

	//默认构造函数
	bintree<K, V>() = default;
	//构造函数，指定key和value
	bintree<K, V>(K n_key, V n_value) :
		key(n_key), value(n_value), isFir(false) {}
	//构造函数，获得一个element的数组，两个权值数组，构造一个最佳二叉树
	bintree<K, V>(const vector<element<K, V> > &ve,
		vector<int> &p, vector<int> &q);

	//destructor
	~bintree<K, V>();

	//assignment operator
	bintree<K, V> &operator=(bintree<K, V> &B);

	//copy constructor
	bintree<K, V>(bintree<K, V> &B);

	//删除左结点并释放空间
	bool delL();

	//删除右结点并释放空间
	bool delR();

	//重置左结点
	bintree<K, V> &setL(K n_key, V n_value);

	//重置右结点
	bintree<K, V> &setR(K n_key, V n_value);

	//返回子节点个数
	int son();

	//判断是不是叶结点
	bool isLeave();

	//对称搜索二叉树，将所有结点都存到数组内，返回这个数组
	vector<element<K, V> > searchtree();

	//搜索关键码为n_key的结点，如果存在就返回其value，
	//否则创建这个结点，创建方法没有使用任何特殊算法
	V &operator[](K n_key);

	//利用当前的二叉树的元素构造一棵最佳二叉树，
	//返回这个新创建的二叉树的指针
	bintree<K, V> *enhance_equal_probability();
};

//重载输出流的左位移运算符，可以使用cout直接输出结点的信息
template <typename K, typename V>
ostream &operator<<(ostream &out, bintree<K, V> &b);

//测试函数
bool test(bintree<int, int> *b);
