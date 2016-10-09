#include "hierarchical_indexed.h"

hierarchical_index::hierarchical_index(int n_size_1, int n_size_2, int n_size_3) {
	size_1 = n_size_1;
	size_2 = n_size_2;
	size_3 = n_size_3;
	content = new HashTable<int, HashTable<int, HashTable<int, double *> *> *>(size_1);
}

void hierarchical_index::enter(const int &index_1, const int &index_2, const int &index_3,
	const double &value_1, const double &value_2, const double &value_3) {
	HashTable<int, HashTable<int, double * > *> *layer_2;
	HashTable<int, double * > *layer_3 = nullptr;
	layer_2 = (*content)[index_1];
	if (layer_2) {
		layer_3 = (*layer_2)[index_2];
	}
	else {
		content->insert(index_1, new HashTable<int, HashTable<int, double * > *>(size_2));
		layer_2 = (*content)[index_1];
	}
	if (!layer_3) {
		layer_2->insert(index_2, new HashTable<int, double * >(size_3));
		layer_3 = (*layer_2)[index_2];
	}
	if ((*layer_3)[index_3] == nullptr) {
		layer_3->insert(index_3, new double[3]);
	}
	double *double_array = (*layer_3)[index_3];
	double_array[0] = value_1;
	double_array[1] = value_2;
	double_array[2] = value_3;
}

void hierarchical_index::get_data(const int &index_1, const int &index_2, const int &index_3,
	double &value_1, double &value_2, double &value_3) {
	const double *double_vec = (*(*(*content)[index_1])[index_2])[index_3];
	value_1 = double_vec[0];
	value_2 = double_vec[1];
	value_3 = double_vec[2];
}

hierarchical_index::~hierarchical_index() {
	if (content) {
		for (int i = 0; i < content->m; ++i) {
			HashTable<int, HashTable<int, double *> *> *tmp_1 = content->ele[i].value;
			if (tmp_1) {
				for (int j = 0; j < tmp_1->m; ++j) {
					HashTable<int, double *> *tmp_2 = tmp_1->ele[j].value;
					if (tmp_2) {
						for (int k = 0; k < tmp_2->m; ++k) {
							double *tmp_3 = tmp_2->ele[j].value;
							if (tmp_3) {
								delete[]tmp_3;
							}
						}
					}
				}
			}
		}
	}
}