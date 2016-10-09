#include <string>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 这个函数可以把小写字母转换成大写字母
void convert_to_capital(string &str) {
	for (int i = 0; i < str.size(); ++i) {
		if (islower(str[i])) {
			str[i] = toupper(str[i]);
		}
	}
}

bool radix_sort_for_text(vector<string> &str_vec) {
	// 记录单词的最大长度
	int max_length(0);
	//转换为大写
	for (int i = 0; i < str_vec.size(); ++i) {
		convert_to_capital(str_vec[i]);
		// 如果有非字母元素，返回 false
		for (auto ch : str_vec[i])
			if (!isupper(ch))
				return false;
	}
	// 找到最大长度
	for (auto c : str_vec)
		max_length = max_length > c.size() ? max_length : c.size();
	// 把不足最大长度单词用空格补全
	for (int i = 0; i < str_vec.size(); ++i) {
		int size = str_vec[i].size();
		for (int j = size; j < max_length; ++j) {
			str_vec[i] += " ";
		}
	}
	// 这是基数排序使用的队列
	vector<queue<string> > queue_vec;
	queue_vec.resize(27);
	// 从最后一位开始排序
	for (int i = max_length - 1; i >= 0; --i) {
		// 收集过程
		for (auto c : str_vec) {
			if (isupper(c[i]))
				queue_vec[c[i] - 'A' + 1].push(c);
			else
				queue_vec[0].push(c);
		}
		int index = 0;
		// 分配过程
		for (int i = 0; i < queue_vec.size(); ++ i) {
			while (!queue_vec[i].empty()) {
				str_vec[index++] = queue_vec[i].front();
				queue_vec[i].pop();
			}
		}
	}
	return true;
}

int main() {
	int size;
	cin >> size;
	vector<string> str_vec;
	str_vec.resize(size);
	for (int i = 0;i < size; ++i) {
		cin >> str_vec[i];
	}
	radix_sort_for_text(str_vec);
	for (auto c : str_vec)
		cerr << c << endl;
	return 0;
}