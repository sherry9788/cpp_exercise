#ifndef ARRAY
#define ARRAY

#include <string>
#include <iostream>
#include <cassert>
#include <iterator>

// DEFAULT_LENGTH is the default length of every
// block.
#define DEFAULT_LENGTH 100
// DEFAULT_RATIO is ratio used to determine
// the length of a new block in the blocklist.
#define DEFAULT_RATIO 1.1
// DEFAULT_TABLE_SIZE is the default number of blocks
// in every blocklist.
#define DEFAULT_TABLE_SIZE 100

// WITH_DATA is a parameter for print_all(int command) 
// function in Array class
#define WITH_DATA 1
// WITHOUT_DATA indicates if the machine just need 
// to print out the numbers of data of every block.
#define WITHOUT_DATA 0

// BLOCK_CHANGED marks if blocks have been changed.
#define BLOCK_CHANGED 1
// TABLE_CHANGED is a return value which means the BlockList
// has been changed.
//?? 还是blocklist？？
#define TABLE_CHANGED 2

template <typename T>
struct Array
{
    friend Array<T> _compress(Array<T>);
    public:

        // pushes a new data onto the tail
        // of the Array.
        int push_back(const T & new_data);

        // pushes a new data onto the head
        // of the Array.
        int push_front(const T & new_data);

        // returns the number of the Array.
        size_t size();

        // returns the refrence of a data in the 
        // given position.
        // ?? refrence?? position? 
        T& operator[](const size_t &n);
        
        // A const version of the [] overload function.
        T operator[](const size_t &n) const;

        // A destruction function. Since the class Array
        // has no pointer, we can just use the default
        // version of destruction function.
        ~Array() = default;

        // n_block_capacity is the number of data 
        // every block could contain, 
        // n_table_capacity is the number of blocks 
        // every BlockList could contain.
        Array(const size_t &n_block_capacity = DEFAULT_LENGTH, 
                const size_t &n_table_capacity = DEFAULT_TABLE_SIZE);

        // Accept a pointer to an array
        // n_data is the number of the data.
        Array(const size_t &n_size, const T* n_data);

        // Accept a istream_iterator.
        Array(std::istream_iterator<T> Begin, std::istream_iterator<T> End);
        
        // Print all data in the Array
        // the command is defined at the beginning of array.h.
        void print_all(const int &command = WITH_DATA);

        // delete the last data of array.
        int pop_back();

        // delete the first data of array.
        int pop_front();
        
        // erase a data at a given position.
        int erase(const size_t &N);

        // insert a data after the Nth data.
        int insert(const size_t &N, const T &new_data);

        // assignment function.
        Array &operator=(const Array &other);

        // copy constructor
        Array(const Array &other);

        // move constructor
        Array(Array &&other) = default;

        // move copt-assignment operator overload
    // ?? copt?
        Array &operator=(Array &&other);

        // resize the BlockList so that every block in
        // the BlockList contains the same number of data
        // move all data in m_bakcward_list to m_forward_list.
        void compress();

        // block is the smallest unit of container which could 
        // store the data.
        struct Block;

        // BlockList is the table which manange the blocks
        struct BlockList;

        // iterator is a random iterator
        struct iterator;

        // const_iterator is a const version of iterator
        struct const_iterator;

        // reverse_iterator is a reverse iterator, and I shouldn't
        // really rewrite it with the help of stl library. 
        //？？？？看不懂
        using reverse_iterator = std::reverse_iterator<iterator>;

        // const_reverse_iterator is a const version of reverse_iterator.
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // the following functions have similar uses as those of vector
        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;

    private:
        
        // push_front data will be saved here
        BlockList m_forward_list;

        // push_front data will be saved here
        BlockList m_backward_list;
        
        // the default number of blocks in every BlockList
        size_t m_default_table_size = DEFAULT_TABLE_SIZE;

        // a function used to help compress function
        Array<T> _compress(Array<T> old);
};

#include "array.cpp.h"
#include "block.h"
#include "blocklist.h"
#include "iterator.h"

#endif
