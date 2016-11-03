#ifndef ARRAYCPP
#define ARRAYCPP

#include "array.h"

template <typename T>
int Array<T>::push_back(T new_data)
{
    return m_forward_list.push_back(new_data);
}

template <typename T>
Array<T>::Array(size_t n_size, T *n_data)
{
    for(int i = 0; i < n_size; ++i)
    {
        push_back(n_data[i]);
    }
}

template <typename T>
Array<T>::Array(size_t n_block_capacity, size_t n_table_capacity):
    m_forward_list(n_table_capacity, n_block_capacity),
    m_backward_list(n_table_capacity, n_block_capacity),
    m_default_table_size(n_table_capacity){}

template <typename T>
Array<T>::Array(const Array &other):
    m_forward_list(other.m_forward_list),
    m_backward_list(other.m_backward_list),
    m_default_table_size(other.m_default_table_size){}

template <typename T>
Array<T> &Array<T>::operator=(const Array &other)
{
    m_forward_list = other.m_forward_list;
    m_backward_list = other.m_backward_list;
    m_default_table_size = other.m_default_table_size;
}

template <typename T>
Array<T> &Array<T>::operator=(Array &&other)
{
    if(m_forward_list.m_table)
    {
        for(int i = 0; i < m_forward_list.m_table_size; ++i)
            delete m_forward_list.m_table[i];
        delete m_forward_list.m_table;
    }
    m_forward_list.m_table_size = other.m_forward_list.m_table_size;
    m_forward_list.m_table_capacity = other.m_forward_list.m_table_capacity;
    m_forward_list.m_default_block_size = other.m_forward_list.m_default_block_size;
    m_forward_list.m_size = other.m_forward_list.m_size;
    m_forward_list.m_table = other.m_forward_list.m_table;

    if(m_backward_list.m_table)
    {
        for(int i = 0; i < m_backward_list.m_table_size; ++i)
            delete m_backward_list.m_table[i];
        delete m_backward_list.m_table;
    }
    m_backward_list.m_table_size = other.m_backward_list.m_table_size;
    m_backward_list.m_table_capacity = other.m_backward_list.m_table_capacity;
    m_backward_list.m_default_block_size = other.m_backward_list.m_default_block_size;
    m_backward_list.m_size = other.m_backward_list.m_size;
    m_backward_list.m_table = other.m_backward_list.m_table;

    other.m_forward_list.m_table = nullptr;
    other.m_backward_list.m_table = nullptr;
    m_default_table_size = other.m_default_table_size;

    return *this;
}

template <typename T>
T &Array<T>::operator[](size_t n)
{
    if(n < m_backward_list.size())
        return m_backward_list[m_backward_list.size() - n - 1];
    else
        return m_forward_list[n - m_backward_list.size()];
}

template <typename T>
void Array<T>::print_all(int command)
{
    std::cout << "m_backward_list:" << std::endl;
    m_backward_list.print_all(command);
    std::cout << "m_forward_list:" << std::endl;
    m_forward_list.print_all(command);
}

template <typename T>
size_t Array<T>::size()
{
    return m_forward_list.size() + m_backward_list.size();
}

template <typename T>
int Array<T>::push_front(T new_data)
{
    return m_backward_list.push_back(new_data);
}

template <typename T>
int Array<T>::pop_back()
{
    return m_forward_list.pop_back();
}

template <typename T>
int Array<T>::pop_front()
{
    return m_backward_list.pop_back();
}

template <typename T>
int Array<T>::erase(size_t N)
{
    if(N < m_backward_list.size())
        return m_backward_list.erase(m_backward_list.size() - N - 1);
    else
        return m_forward_list.erase(N - m_backward_list.size());
}

template <typename T>
int Array<T>::insert(size_t N, T new_data)
{
    if(N < m_backward_list.size())
        return m_backward_list.insert(m_backward_list.size() - N - 1, new_data);
    else
        return m_forward_list.insert(N - m_backward_list.size(), new_data);
}

template <typename T>
T Array<T>::get(size_t N) const 
{
    if(N < m_backward_list.size())
        return m_backward_list.get(m_backward_list.size() - N - 1);
    else
        return m_forward_list.get(N - m_backward_list.size());
}

template <typename T>
void Array<T>::compress()
{
    *this = _compress(*this);
}

template <typename T>
Array<T> Array<T>::_compress(Array<T> old)
{
    Array<T> ret_array(old.m_default_table_size,
            old.m_forward_list.m_default_block_size);
    for(int i = 0 ; i < old.size(); ++i)
        ret_array.push_back(old.get(i));
    return ret_array;
}

#endif
