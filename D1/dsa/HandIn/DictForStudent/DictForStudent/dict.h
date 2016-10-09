#ifndef DICT
#define DICT

#include <vector>

//element���Ǵ洢ÿ���ֵ�Ԫ�ص���
#include "element.h"
//quick�ǿ�������ĺ���
#include "quicksort.h"

 template <typename K, typename V>
struct dict
{
	//data
	element<K, V> *Dic;		//�ֵ�Ԫ�ض�����һ��������
	size_t Max;				//Max���ֵ���������
	size_t n;				//n���ֵ�ĵ�ǰԪ������

	//function

	//constructor
	dict<K, V>(size_t n_Max = INT_MAX); 
	
	//destructor
	~dict();

	//assignment function
	dict &operator=(const dict &D);

	//������
	void sort();

	//���뺯�������뺯������������
	dict<K, V> &insert(const K &key, const V &value);

	//��ӡ�ֵ��е�����Ԫ��
	dict<K, V> &print();

	//[]�з���key�����Կ��ټ�������Ӧvalue
	V operator[](K key);
};

 template <typename K, typename V>
void dict<K, V>::sort() {
	//��Ϊ���������㷨ʹ�õ���vector���飬������ת��ele
	vector<element<K, V> > ele_vec;

	for (unsigned i = 0; i < n; ++i) 
		ele_vec.push_back(Dic[i]);

	//����������
	quicksort(ele_vec);

	//vector�Ѿ��ź��򣬽����е�Ԫ�����ηŻ�ԭ������
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
	++n;								 //����������
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
	//��������ʹ���˶�������
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
	//���û�м��������ʹ���һ��Ĭ�Ϲ������ʱ����������
	return V();
}

#endif