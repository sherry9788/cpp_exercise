#ifndef ELE
#define ELE

//element是存储字典元素的类
template <typename K, typename V>
struct element
{
public:
	K key;			//关键码
	V value;		//值

	//constructor
	element<K, V>(K n_key, V n_value);

	//default constructor
	element<K, V>() = default;

	//谓语
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