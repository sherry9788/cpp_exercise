#ifndef CONSTITER
#define CONSTITER

#include <iterator>
#include <string>
#include <cassert>

#include "array.h"
#include "blocklist.h"
#include "block.h"

template <typename T>
struct Array<T>::const_iterator
{
    public:
        using value_type = T;
        using difference_type = size_t;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::random_access_iterator_tag;

        const_iterator() = default;
        const_iterator(Array<T>::Block **n_f_table, const size_t &n_f_table_size,
                Array<T>::Block **n_b_table, const size_t &n_b_table_size,
                const size_t &n_f_size, const size_t &n_b_size,
                const size_t &n_curr_pos = 0);
        ~const_iterator() = default;
        const_iterator(const const_iterator &other);
        const_iterator(const_iterator &&other) = default;

        const_iterator &operator=(const const_iterator &other);
        const_iterator &operator=(const_iterator &&other) = default;

        reference operator[](const size_t &N);
        reference operator*() const;

        const_iterator operator++();
        const_iterator operator++(int Nothing);
        const_iterator operator--();
        const_iterator operator--(int Nothing);

        const_iterator operator-(const size_t &N) const;
        const_iterator operator+(const size_t &N) const;
        const_iterator operator-=(const size_t &N);
        const_iterator operator+=(const size_t &N);

        pointer operator->();
        
        bool operator!=(const const_iterator &right_iter) const;
        bool operator<=(const const_iterator &right_iter) const;
        bool operator>=(const const_iterator &right_iter) const;
        bool operator==(const const_iterator &right_iter) const;
        bool operator<(const const_iterator &right_iter) const;
        bool operator>(const const_iterator &right_iter) const;

        difference_type operator-(const const_iterator &right_iter) const;

    private:
        size_t m_curr_pos = 0;
        size_t m_f_table_size = 0;
        size_t m_f_size = 0;
        size_t m_b_table_size = 0;
        size_t m_b_size = 0;
        Array<T>::Block **m_f_table = nullptr;
        Array<T>::Block **m_b_table = nullptr;
};

#include "constiterator.cpp.h"

#endif
