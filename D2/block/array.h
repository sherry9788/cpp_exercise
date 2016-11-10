#ifndef ARRAY
#define ARRAY

#include <string>
#include <iostream>
#include <cassert>
#include <iterator>

// DEFAULT_LENGTH is the default length of every
// block.
#define DEFAULT_LENGTH 100
// DEFAULT_RATIO is ratio which is used to determine
// the length of a new block in the blocklist.
#define DEFAULT_RATIO 1.1
// DEFAULT_TABLE_SIZE is the default number of blocks
// for every blocklist.
#define DEFAULT_TABLE_SIZE 100

// WITH_DATA is a parameter for print_all(int command) 
// function in Array class
#define WITH_DATA 1
// WITHOUT_DATA is nothin different from WITH_DATA but
// means that the machine just need to print the numbers
// of data of every block.
#define WITHOUT_DATA 0

// BLOCK_CHANGED is a return value for some functions,
// it means that the blocks have been changed.
#define BLOCK_CHANGED 1
// TABLE_CHANGED is a return value which means the BlockList
// has been changed.
#define TABLE_CHANGED 2

template <typename T>
struct Array
{
    friend Array<T> _compress(Array<T>);
    public:

        // push_back can push a new data onto the tail
        // of the Array.
        int push_back(const T & new_data);

        // push_front can push a new data onto the head
        // of the Array.
        int push_front(const T & new_data);

        // size() can return the number of the Array.
        size_t size();

        // [] can return the refrence of a data in the 
        // given position.
        T& operator[](const size_t &n);
        
        // A const version of the [] overload function.
        T operator[](const size_t &n) const;

        // A destruction function. Cause the class Array
        // has no pointer, we can just use the default
        // version of destruction function.
        ~Array() = default;

        // n_block_capacity is the number of data every
        // block could contains, n_table_capacity is the
        // number of blocks every BlockList could contains.
        Array(const size_t &n_block_capacity = DEFAULT_LENGTH, 
                const size_t &n_table_capacity = DEFAULT_TABLE_SIZE);

        // Accept a pointer to an array, n_data is the number
        // of the data.
        Array(const size_t &n_size, const T* n_data);

        // Accept a istream_iterator.
        Array(std::istream_iterator<T> Begin, std::istream_iterator<T> End);
        
        // Print all data of the Array, the command is defined
        // on the head of array.h file.
        void print_all(const int &command = WITH_DATA);

        // delete the last data of array.
        int pop_back();

        // delete the first data of array.
        int pop_front();
        
        // erase a data in the given position.
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
        Array &operator=(Array &&other);

        // resize the BlockList to make all blocks in
        // every BlockList contains the same number of
        // data and move all data in ther m_bakcward_list
        // to m_forward_list.
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
        using reverse_iterator = std::reverse_iterator<iterator>;

        // const_reverse_iterator is a const version of reverse_iterator.
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // the following functions has the similar functions with
        // vector and is easy to comprehend
        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;

    private:
        
        // is you push_back a data to the array, the data would
        // be stored here
        BlockList m_forward_list;

        // is you push_front a data to the array, the data would
        // be stored here
        BlockList m_backward_list;
        
        // the defalut number of blocks of every BlockList
        size_t m_default_table_size = DEFAULT_TABLE_SIZE;

        // a function used to help compress function
        Array<T> _compress(Array<T> old);
};

#include "array.cpp.h"
#include "block.h"
#include "blocklist.h"
#include "iterator.h"

#endif
