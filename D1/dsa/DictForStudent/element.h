#ifndef ELE
#define ELE

//element�Ǵ洢�ֵ�Ԫ�ص���
template <typename K, typename V>
struct element
{
public:
	K key;			//�ؼ���
	V value;		//ֵ

	//constructor
	element<K, V>(K n_key, V n_value);

	//default constructor
	element<K, V>() = default;

	//ν��
	bool operator<(const element<K, V> &other) {
		return key < other.key;
	}
	bool operator>(const element<K, V> &other) {
		return key > other.key;
	}
	bool operator==(const element<K, V> &other) {
		return key == other.key;
	}
	bool operator<=(const element<K, V> &other) {
		return key <= other.key;
	}
	bool operator>=(const element<K, V> &other) {
		return key >= other.key;
	}
};

template<typename K, typename V>
element<K, V>::element(K n_key, V n_value) {
	key = n_key;
	value = n_value;
}

#endif