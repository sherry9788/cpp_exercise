#include "test.h"

void test_bubble_sort(element<int, int> test_element) {
	cerr << "bubble sort test" << endl;
	double time_recorder = clock();
	int n_compare = 0;

	test_element.bubbleSort(n_compare);

	cerr << "sorting time: " << clock() - time_recorder << " ms" << endl;
	cerr << "the number of the comparision: " << n_compare << endl;
	system("pause");
	cerr << endl;
}

void test_quick_sort(vector<int> test_vector) {
	cerr << "quick sort test" << endl;
	double time_recorder = clock();
	int n_compare = 0;

	quicksort(test_vector, n_compare);

	cerr << "sorting time: " << clock() - time_recorder << " ms" << endl;
	cerr << "the number of the comparision: " << n_compare << endl;
	system("pause");
	cerr << endl;
}

void test_insert_sort(element<int, int> test_element) {
	cerr << "insert sort test" << endl;
	double time_recorder = clock();
	int n_compare = 0;

	test_element.insertsort(n_compare);

	cerr << "sorting time: " << clock() - time_recorder << " ms" << endl;
	cerr << "the number of the comparision: " << n_compare << endl;
	system("pause");
	cerr << endl;
}

void test_merge_sort(vector<int> test_vector) {
	cerr << "merge sort test" << endl;
	double time_recorder = clock();
	int n_compare = 0;

	mergeSort(test_vector, n_compare);

	cerr << "sorting time: " << clock() - time_recorder << " ms" << endl;
	cerr << "the number of the comparision: " << n_compare << endl;
	system("pause");
	cerr << endl;
}

void test_radix_sort(vector<int> test_vector) {
	cerr << "radix sort test" << endl;
	double time_recorder = clock();
	int n_compare = 0;

	radixsort(test_vector, n_compare);

	cerr << "sorting time: " << clock() - time_recorder << " ms" << endl;
	cerr << "the number of the comparision: " << n_compare << endl;
	system("pause");
	cerr << endl;
}

void test_select_sort(element<int, int> test_element) {
	cerr << "select sort test" << endl;
	double time_recorder = clock();
	int n_compare = 0;

	test_element.select_sort(n_compare);

	cerr << "sorting time: " << clock() - time_recorder << " ms" << endl;
	cerr << "the number of the comparision: " << n_compare << endl;
	system("pause");
	cerr << endl;
}

void test_heap_sort(element<int, int> test_element) {
	cerr << "heap sort test" << endl;
	double time_recorder = clock();
	int n_compare = 0;

	test_element.heap_sort(n_compare);

	cerr << "sorting time: " << clock() - time_recorder << " ms" << endl;
	cerr << "the number of the comparision: " << n_compare << endl;
	system("pause");
	cerr << endl;
}