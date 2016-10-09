#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <map>

#include "stack.h"

using namespace std;

//element����������ÿ��������Ϣ
template <typename K, typename V>
struct element{
	K key;
	V value;
	element(K n_key, V n_value) :
		key(n_key), value(n_value) {}
};

//���㵱ǰ����Rֵ������λ�ã�
int cal_r(map<vector<int>, int> &C, int i, int j, int &r);

//bintree�Ƕ�����������KΪ�ؼ��룬VΪ��ֵ
template <typename K, typename V>
struct bintree
{
	//data
public:
	K key;								//�ؼ���
	V value;							//�����ֵ
	bintree *m_L = nullptr;				//left	
	bintree *m_R = nullptr;				//rgiht
	bool isFir = true;					//��¼�ǲ��ǵ�һ��������

	//function
public:

	//Ĭ�Ϲ��캯��
	bintree<K, V>() = default;
	//���캯����ָ��key��value
	bintree<K, V>(K n_key, V n_value) :
		key(n_key), value(n_value), isFir(false) {}
	//���캯�������һ��element�����飬����Ȩֵ���飬����һ����Ѷ�����
	bintree<K, V>(const vector<element<K, V> > &ve,
		vector<int> &p, vector<int> &q);

	//destructor
	~bintree<K, V>();

	//assignment operator
	bintree<K, V> &operator=(bintree<K, V> &B);

	//copy constructor
	bintree<K, V>(bintree<K, V> &B);

	//ɾ�����㲢�ͷſռ�
	bool delL();

	//ɾ���ҽ�㲢�ͷſռ�
	bool delR();

	//��������
	bintree<K, V> &setL(K n_key, V n_value);

	//�����ҽ��
	bintree<K, V> &setR(K n_key, V n_value);

	//�����ӽڵ����
	int son();

	//�ж��ǲ���Ҷ���
	bool isLeave();

	//�Գ������������������н�㶼�浽�����ڣ������������
	vector<element<K, V> > searchtree();

	//�����ؼ���Ϊn_key�Ľ�㣬������ھͷ�����value��
	//���򴴽������㣬��������û��ʹ���κ������㷨
	V &operator[](K n_key);

	//���õ�ǰ�Ķ�������Ԫ�ع���һ����Ѷ�������
	//��������´����Ķ�������ָ��
	bintree<K, V> *enhance_equal_probability();
};

//�������������λ�������������ʹ��coutֱ�����������Ϣ
template <typename K, typename V>
ostream &operator<<(ostream &out, bintree<K, V> &b);

//���Ժ���
bool test(bintree<int, int> *b);
