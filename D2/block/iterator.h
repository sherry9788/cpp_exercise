#ifndef ITER
#define ITER

#include <iterator>
#include <string>
#include <cassert>

#include "array.h"
#include "blocklist.h"
#include "block.h"

template <typename T>
struct Array<T>::iterator
{
    public:
        using value_type = T;
        using difference_type = size_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag;

        iterator() = default;
        iterator(Array<T>::Block **n_f_table, const size_t &n_f_table_size,
                Array<T>::Block **n_b_table, const size_t &n_b_table_size,
                const size_t &n_f_size, const size_t &n_b_size,
                const size_t &n_curr_pos = 0);
        ~iterator() = default;
        iterator(const iterator &other);
        iterator(iterator &&other) = default;

        iterator &operator=(const iterator &other);
        iterator &operator=(iterator &&other) = default;

        reference operator[](const size_t &N);
        reference operator*() const;

        iterator operator++();
        iterator operator++(int Nothing);
        iterator operator--();
        iterator operator--(int Nothing);

        iterator operator-(const size_t &N) const;
        iterator operator+(const size_t &N) const;
        iterator operator+=(const size_t &N);
        iterator operator-=(const size_t &N);

        pointer operator->();
        
        bool operator!=(const iterator &right_iter) const;
        bool operator<=(const iterator &right_iter) const;
        bool operator>=(const iterator &right_iter) const;
        bool operator==(const iterator &right_iter) const;
        bool operator<(const iterator &right_iter) const;
        bool operator>(const iterator &right_iter) const;

        difference_type operator-(const iterator &right_iter) const;

    private:
        size_t m_curr_pos = 0;
        size_t m_f_table_size = 0;
        size_t m_f_size = 0;
        size_t m_b_table_size = 0;
        size_t m_b_size = 0;
        Array<T>::Block **m_f_table = nullptr;
        Array<T>::Block **m_b_table = nullptr;
};

#include "iterator.cpp.h"

#endif
