#include "test.h"
#include <fstream>

int main() {
	srand(0);
	vector<int> ivec;
	for (int i = 0; i < 2000; ++i) {
		ivec.push_back(rand());
	}
	element<int, int> ini_ele(ivec[0]);
	for (unsigned i = 1; i < ivec.size(); ++i)
		ini_ele.add(ivec[i]);
	
	test_bubble_sort(ini_ele);
	test_heap_sort(ini_ele);
	test_insert_sort(ini_ele);
	test_merge_sort(ivec);
	test_quick_sort(ivec);
	test_radix_sort(ivec);
	test_select_sort(ini_ele);
	
	int tmp_compare;
	int tmp_move;
	quicksort(ivec, tmp_compare, tmp_move);
	element<int, int> order_ele(ivec[0]);
	for (unsigned i = 1; i < ivec.size(); ++i)
		order_ele.add(ivec[i]);

	test_bubble_sort(order_ele);
	test_heap_sort(order_ele);
	test_insert_sort(order_ele);
	test_merge_sort(ivec);
	test_quick_sort(ivec);
	test_radix_sort(ivec);
	test_select_sort(order_ele);


	r_quicksort(ivec);
	element<int, int> reverse_ele(ivec[0]);
	for (unsigned i = 1; i < ivec.size(); ++i)
		reverse_ele.add(ivec[i]);

	test_bubble_sort(reverse_ele);
	test_heap_sort(reverse_ele);
	test_insert_sort(reverse_ele);
	test_merge_sort(ivec);
	test_quick_sort(ivec);
	test_radix_sort(ivec);
	test_select_sort(reverse_ele);
	
	return 0;
}