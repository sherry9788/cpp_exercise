#ifndef CONSTITERCPP
#define CONSTITERCPP

#include "constiterator.h"

template <typename T>
Array<T>::const_iterator::const_iterator(Array<T>::Block **n_f_table, const size_t &n_f_table_size,
            Array<T>::Block **n_b_table, const size_t &n_b_table_size,
            const size_t &n_f_size, const size_t &n_b_size,
            const size_t &n_curr_pos):
    m_f_size(n_f_size), m_f_table(n_f_table), m_f_table_size(n_f_table_size),
    m_b_size(n_b_size), m_b_table(n_b_table), m_b_table_size(n_b_table_size),
    m_curr_pos(n_curr_pos) {}
    
template <typename T>
Array<T>::const_iterator::const_iterator(const const_iterator &right_iter):
    m_f_size(right_iter.m_f_size), m_f_table(right_iter.m_f_table), 
    m_f_table_size(right_iter.m_f_table_size),
    m_b_size(right_iter.m_b_size), m_b_table(right_iter.m_b_table), 
    m_b_table_size(right_iter.m_b_table_size),
    m_curr_pos(right_iter.m_curr_pos) {}
    

template <typename T>
typename Array<T>::const_iterator &Array<T>::const_iterator::operator=(const const_iterator &other)
{
    m_f_size = other.m_f_size;
    m_f_table = other.m_f_table;
    m_f_table_size = other.m_f_table_size;

    m_b_size = other.m_b_size;
    m_b_table = other.m_b_table;
    m_b_table_size = other.m_b_table_size;

    m_curr_pos = other.m_curr_pos;
    return *this;
}

template <typename T>
typename Array<T>::const_iterator::reference 
Array<T>::const_iterator::operator[](const size_t &N)
{
    assert(N + m_curr_pos < m_f_size + m_b_size && N + m_curr_pos >= 0);
    size_t pos = N + m_curr_pos;
    if(pos < m_b_size)
    {
        pos = m_b_size - pos - 1;
        size_t i = 0;
        while(pos >= m_b_table[i]->m_size)
        {
            ++i;
            pos -= m_b_table[i]->m_size;
        }
        return (*m_b_table[i])[pos];
    }
    else
    {
        pos = pos - m_b_size;
        size_t i = 0;
        while(pos >= m_f_table[i]->m_size)
        {
            ++i;
            pos -= m_f_table[i]->m_size;
        }
        return (*m_f_table[i])[pos];
    }
}

template <typename T>
typename Array<T>::const_iterator::reference
Array<T>::const_iterator::operator*()
{
    size_t pos = m_curr_pos;
    if(pos < m_b_size)
    {
        pos = m_b_size - pos - 1;
        size_t i = 0;
        while(pos >= m_b_table[i]->m_size)
        {
            ++i;
            pos -= m_b_table[i]->m_size;
        }
        return (*m_b_table[i])[pos];
    }
    else
    {
        pos = pos - m_b_size;
        size_t i = 0;
        while(pos >= m_f_table[i]->m_size)
        {
            ++i;
            pos -= m_f_table[i]->m_size;
        }
        return (*m_f_table[i])[pos];
    }
}

template <typename T>
typename Array<T>::const_iterator Array<T>::const_iterator::operator++()
{
    assert(m_curr_pos <= m_b_size + m_f_size - 1);
    ++m_curr_pos;
    return *this;
}

template <typename T>
typename Array<T>::const_iterator Array<T>::const_iterator::operator++(int Nothing)
{
    --Nothing;
    const_iterator ret = *this;
    assert(m_curr_pos < m_b_size + m_f_size - 1);
    ++m_curr_pos;
    return ret;
}

template <typename T>
typename Array<T>::const_iterator Array<T>::const_iterator::operator--()
{
    assert(m_curr_pos > 0);
    --m_curr_pos;
    return *this;
}

template <typename T>
typename Array<T>::const_iterator Array<T>::const_iterator::operator--(int Nothing)
{
    --Nothing;
    const_iterator ret = *this;
    assert(m_curr_pos > 0);
    --m_curr_pos;
    return ret;
}

template <typename T>
typename Array<T>::const_iterator Array<T>::const_iterator::operator+(const size_t &N)
{
    assert(N + m_curr_pos <= m_b_size + m_f_size);
    m_curr_pos += N;
    return *this;
}

template <typename T>
typename Array<T>::const_iterator Array<T>::const_iterator::operator-(const size_t &N)
{
    assert(m_curr_pos - N >= 0);
    m_curr_pos -= N;
    return *this;
}

template <typename T>
typename Array<T>::const_iterator::pointer Array<T>::const_iterator::operator->()
{
    size_t pos = m_curr_pos;
    if(pos < m_b_size)
    {
        pos = m_b_size - pos - 1;
        size_t i = 0;
        while(pos >= m_b_table[i]->m_size)
        {
            ++i;
            pos -= m_b_table[i]->m_size;
        }
        return &(*m_b_table[i])[pos];
    }
    else
    {
        pos = pos - m_b_size;
        size_t i = 0;
        while(pos >= m_f_table[i]->m_size)
        {
            ++i;
            pos -= m_f_table[i]->m_size;
        }
        return &(*m_f_table[i])[pos];
    }
}

template <typename T>
bool Array<T>::const_iterator::operator==(const 
        typename Array<T>::const_iterator &right_iter) const
{
    assert(m_f_table == right_iter.m_f_table);
    return m_curr_pos == right_iter.m_curr_pos;
}

template <typename T>
bool Array<T>::const_iterator::operator!=(const 
        typename Array<T>::const_iterator &right_iter) const
{
    assert(m_f_table == right_iter.m_f_table);
    return m_curr_pos != right_iter.m_curr_pos;
}

template <typename T>
bool Array<T>::const_iterator::operator<=(const 
        typename Array<T>::const_iterator &right_iter) const
{
    assert(m_f_table == right_iter.m_f_table);
    return m_curr_pos <= right_iter.m_curr_pos;
}

template <typename T>
bool Array<T>::const_iterator::operator>=(const 
        typename Array<T>::const_iterator &right_iter) const
{
    assert(m_f_table == right_iter.m_f_table);
    return m_curr_pos >= right_iter.m_curr_pos;
}

template <typename T>
bool Array<T>::const_iterator::operator<(const 
        typename Array<T>::const_iterator &right_iter) const
{
    assert(m_f_table == right_iter.m_f_table);
    return m_curr_pos < right_iter.m_curr_pos;
}

template <typename T>
bool Array<T>::const_iterator::operator>(const 
        typename Array<T>::const_iterator &right_iter) const
{
    assert(m_f_table == right_iter.m_f_table);
    return m_curr_pos > right_iter.m_curr_pos;
}

template <typename T>
typename Array<T>::const_iterator::difference_type 
Array<T>::const_iterator::operator-(const typename Array<T>::const_iterator &right_iter) const
{
    assert(m_f_table == right_iter.m_f_table);
    return m_curr_pos - right_iter.m_curr_pos;
}

#endif
