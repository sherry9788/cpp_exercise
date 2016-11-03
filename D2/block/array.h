#ifndef ARRAY
#define ARRAY

#include <string>
#include <iostream>
#include <cassert>

#define DEFAULT_LENGTH 100
#define DEFAULT_RATIO 1.1
#define DEFAULT_TABLE_SIZE 100

#define WITH_DATA 1
#define WITHOUT_DATA 0

#define BLOCK_CHANGED 1
#define TABLE_CHANGED 2

template <typename T>
struct Array
{
    friend Array<T> _compress(Array<T>);
    public:

        int push_back(T new_data);
        int push_front(T new_data);
        size_t size();
        T& operator[](size_t n);

        ~Array() = default;
        Array(size_t n_block_capacity = DEFAULT_LENGTH, 
                size_t n_table_capacity = DEFAULT_TABLE_SIZE);

        Array(size_t n_size, T* n_data);
        
        void print_all(int command);

        int pop_back();
        int pop_front();
        
        int erase(size_t N);

        int insert(size_t N, T new_data);

        Array &operator=(const Array &other);
        Array(const Array &other);
        Array(Array &&other) = default;
        Array &operator=(Array &&other);

        void compress();

        struct Block;
        struct BlockList;

    private:
        
        BlockList m_forward_list;
        BlockList m_backward_list;
        
        size_t m_default_table_size = DEFAULT_TABLE_SIZE;

        T get(size_t N) const;
        Array<T> _compress(Array<T> old);
};

#include "array.cpp.h"
#include "block.h"
#include "blocklist.h"

#endif
