#ifndef ARRAY
#define ARRAY

#include <string>
#include <iostream>
#include <cassert>
#include <iterator>

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

        int push_back(const T & new_data);
        int push_front(const T & new_data);
        size_t size();
        T& operator[](const size_t &n);
        T operator[](const size_t &n) const;

        ~Array() = default;
        Array(const size_t &n_block_capacity = DEFAULT_LENGTH, 
                const size_t &n_table_capacity = DEFAULT_TABLE_SIZE);

        Array(const size_t &n_size, const T* n_data);
        Array(std::istream_iterator<T> Begin, std::istream_iterator<T> End);
        
        void print_all(const int &command = WITH_DATA);

        int pop_back();
        int pop_front();
        
        int erase(const size_t &N);

        int insert(const size_t &N, const T &new_data);

        Array &operator=(const Array &other);
        Array(const Array &other);
        Array(Array &&other) = default;
        Array &operator=(Array &&other);

        void compress();

        struct Block;
        struct BlockList;
        struct iterator;
        struct const_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;

    private:
        
        BlockList m_forward_list;
        BlockList m_backward_list;
        
        size_t m_default_table_size = DEFAULT_TABLE_SIZE;

        Array<T> _compress(Array<T> old);
};

#include "array.cpp.h"
#include "block.h"
#include "blocklist.h"
#include "iterator.h"

#endif
