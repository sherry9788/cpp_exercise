#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

template <typename T>
void merge(vector<vector<T> > &vec) {
	if (vec.size() == 1)
		return;
	for (int i = 0; i + 1 < vec.size(); ++i) {
		auto iter_1 = vec.begin() + i;
		auto iter_2 = vec.begin() + i + 1;
		auto iter_3 = iter_1->begin();
		auto iter_4 = iter_2->begin();
		vector<T> tmp;
		while (iter_3 != iter_1->end() && iter_4 != iter_2->end()) {
			if (*iter_3 < *iter_4) {
				tmp.push_back(*iter_3);
				++iter_3;
			}
			else {
				tmp.push_back(*iter_4);
				++iter_4;
			}
		}
		while (iter_3 != iter_1->end()) {
			tmp.push_back(*iter_3);
			++iter_3;
		}
		while (iter_4 != iter_2->end()) {
			tmp.push_back(*iter_4);
			++iter_4;
		}
		*iter_1 = tmp;
		vec.erase(iter_2);
	}
	merge(vec);
}

template <typename T>
void mergeSort(vector<T> &vec) {
	vector<vector<T> > tmp;
	for (auto c : vec)
		tmp.push_back(vector<T>{c});
	merge(tmp);
	int i = 0;
	vec = tmp[0];
}

int main() {
	int n;
loop:
	vector<int> vec;
	cin >> n;
	if (n < 1)
		return 0;
	while (--n != 0)
		vec.push_back(rand());
	double x = clock();
	mergeSort(vec);
	cerr << clock() - x << endl;
	goto loop;
	return 0;
}
