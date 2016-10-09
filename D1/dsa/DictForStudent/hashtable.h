#ifndef HASH
#define HASH

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "element.h"

using namespace std;

//HashTable�ǹ�ϣ�����
 template <typename K, typename V>
struct HashTable
{
	//data
public:
	int m = 0;						//��ϣ�������
	int n_collision = 0;			//��ײ����
	vector<int> position_collision; //��ײλ��
	element<K, V> *ele = nullptr;	//�洢Ԫ�ص�����

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

	//��������
	V operator[](K n_key);

	//delete function
	V del(K n_key);
	
	//hash function
	int h(K n_key);

	//������������
	bool linear_search(K n_key, int &pos);
	
	//���뺯��
	void insert(K n_key, V n_value);

	//���뺯��
	void insert(element<K, V> n_ele);
};

 template <typename K, typename V>
HashTable<K, V>::HashTable(int n_m) {
	m = n_m;
	ele = new element<K, V>[m];
	//���û���������飬�ͽ�������
	assert(ele);
	//�������е�����Ԫ�عؼ����ÿ�
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
	//��ini��¼���ȷ���Ĺ�ϣֵ
	int ini = index;		
	if (ele[index].key == n_key)
		//����Ѿ��ҵ�Ԫ�أ�ֱ�ӷ���
		return ele[index].value;
	//����˳���ң�֪���ҵ����߻ص�ԭ���Ĺ�ϣֵλ��
	for (++index; index != ini; ++index) {
		index %= m;
		if (ele[index].key == n_key)
			return ele[index].value;
	}
	//���û���ҵ����ʹ���һ����ʱ����������
	cerr << "Not Found";
	return V();
}

 template <typename K, typename V>
int HashTable<K, V>::h(K n_key) {
	//��ϣֵ���㷨�ǰ�string��ǰ�������ֶ�Ӧ���ĸ�char�ҳ�������Ӳ�ģ�����Ĵ�С
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
	//�����������ײ����ײ��¼��Ҫ��һ
	++n_collision;
	//ͬʱҪ��¼����ײ��λ��
	position_collision.push_back(pos);
	//����һ����λ��
	for (++index; index != ini; ++index) {
		index %= m;
		if (ele[index].key == V()) {
			pos = index;
			return true;
		}
	}
	//û���ҵ�˵����ϣ������������false
	return false;
}

 template <typename K, typename V>
void HashTable<K, V>::insert(K n_key, V n_value) {
	int pos;
	//�����ϣ��������ֱ����ֹ����
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
	//ret��¼����ɾ����Ԫ�ص�ֵ
	V ret;
	int index = h(n_key);
	int ini = index;
	//����Ѿ��ҵ����ͼ�¼��ֵ
	if (ele[index].key == n_key)
		ret = ele[index].value;
	else {
		//���û���ҵ����͵���index��һֱ����Ѱ�ң�ֱ���ҵ�Ϊֹ
		for (++index; index != ini; ++index) {
			index %= m;
			if (ele[index].key == n_key)
				ret = ele[index].value;
		}
		//���û�и�Ԫ�أ���ֱ�ӷ���һ��Ĭ�Ϲ�����ʱ����
		if (index == ini)
			return V();
	}
	
	//space��¼��ǰ��λ��α��ַ
	int space = index;
	//next_space��¼��һ���յ�ַ��λ��
	int next_space = index + 1;
	//whileѭ������λ��һ���յ�ַ
	while (ele[next_space].key != K()) {
		++next_space;
		if (next_space == m)
			next_space = 0;
	}

	//�ÿ�Ҫɾ��Ԫ�صĹؼ���
	ele[index].key = K();

	//����α��ַ
	++index;
	//���ѭ������0
	if (index == m)
		index = 0;
	
	if(next_space < index)
		//����ѭ�������
		while (index != next_space) {
			if (h(ele[index].key) < space) {
				//�����ǰԪ�ز��ܱ�������
				ele[space].key = ele[index].key;
				ele[space].value = ele[index].value;
				//�ƶ���λ
				space = index;
			}
			++index;
			//ѭ������0
			if (index == m)
				index = 0;
		}
	else
		//δ����ѭ�������
		while (index != next_space) {
			if (h(ele[index].key) < space || h(ele[index].key) > next_space) {
				//�����ǰԪ�ز��ܱ�������
				ele[space].key = ele[index].key;
				ele[space].value = ele[index].value;
				//�ƶ���λ
				space = index;
			}
			++index;
		}
	
	return ret;
}

#endif