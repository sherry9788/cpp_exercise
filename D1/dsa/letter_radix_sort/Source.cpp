#include <string>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ����������԰�Сд��ĸת���ɴ�д��ĸ
void convert_to_capital(string &str) {
	for (int i = 0; i < str.size(); ++i) {
		if (islower(str[i])) {
			str[i] = toupper(str[i]);
		}
	}
}

bool radix_sort_for_text(vector<string> &str_vec) {
	// ��¼���ʵ���󳤶�
	int max_length(0);
	//ת��Ϊ��д
	for (int i = 0; i < str_vec.size(); ++i) {
		convert_to_capital(str_vec[i]);
		// ����з���ĸԪ�أ����� false
		for (auto ch : str_vec[i])
			if (!isupper(ch))
				return false;
	}
	// �ҵ���󳤶�
	for (auto c : str_vec)
		max_length = max_length > c.size() ? max_length : c.size();
	// �Ѳ�����󳤶ȵ����ÿո�ȫ
	for (int i = 0; i < str_vec.size(); ++i) {
		int size = str_vec[i].size();
		for (int j = size; j < max_length; ++j) {
			str_vec[i] += " ";
		}
	}
	// ���ǻ�������ʹ�õĶ���
	vector<queue<string> > queue_vec;
	queue_vec.resize(27);
	// �����һλ��ʼ����
	for (int i = max_length - 1; i >= 0; --i) {
		// �ռ�����
		for (auto c : str_vec) {
			if (isupper(c[i]))
				queue_vec[c[i] - 'A' + 1].push(c);
			else
				queue_vec[0].push(c);
		}
		int index = 0;
		// �������
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