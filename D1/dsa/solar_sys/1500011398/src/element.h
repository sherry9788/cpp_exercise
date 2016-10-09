#ifndef ELEMENT
#define ELEMENT

// element structure
// it is wrote for hashtable
template <typename K, typename V>
struct element
{
public:
	// key
	K key;
	// value
	V value;		

	//constructor
	element<K, V>(K n_key, V n_value);

	//default constructor
	element<K, V>() = default;

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