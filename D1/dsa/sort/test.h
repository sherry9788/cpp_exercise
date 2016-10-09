#ifndef TEST
#define TEST

#include "element.h"
#include "quick_sort.h"
#include "radix_sort.h"
#include "merge_sort.h"

// test 开头的函数均为测试函数

void test_bubble_sort(element<int, int> test_element);

void test_quick_sort(vector<int> test_vector);

void test_insert_sort(element<int, int> test_element);

void test_merge_sort(vector<int> test_vector);

void test_radix_sort(vector<int> test_vector);

void test_select_sort(element<int, int> test_element);

void test_heap_sort(element<int, int> test_element);

#endif