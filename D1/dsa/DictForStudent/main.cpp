#include <fstream>
#include <vector>

#include "hashtable.h"
#include "dict.h"

using namespace std;


//获取学生的信息，存到两个vector数组中
bool getList(vector<string> &svec, vector<string> &ivec) {
	fstream file_in("list.txt", fstream::in);
	string s, i;
	while (file_in >> s) {
		file_in >> i;
		if (!file_in)
			return false;
		file_in >> s;
		if (!file_in)
			return false;
		svec.push_back(s);
		ivec.push_back(i);
	}
	return true;
}

//测试字典函数
void test_dict() {
	vector<string> name;
	vector<string> number;
	assert(getList(name, number));
	dict<string, string> D(1000);
	for (unsigned i = 0; i < name.size(); ++i)
		D.insert(number[i], name[i]);
	D.sort();
	D.print();
	string i;
loop:
	cin >> i;
	cerr << D[i] << endl;
	goto loop;
}

//测试哈希表函数
void test_hash() {
	vector<string> name;
	vector<string> number;
	assert(getList(name, number));
	HashTable<string, string> H(100);
	for (unsigned i = 0; i < name.size(); ++i)
		H.insert(name[i], number[i]);
	string Name;
	while (cin >> Name) {
		if (Name == "0")
			break;
		cerr << H[Name] << endl;
	}
	cin >> Name;
	H.del(Name);
	while (cin >> Name) {
		if (Name == "0")
			break;
		cerr << H[Name] << endl;
	}
}

int main() {
	test_hash();
	return 0;
}