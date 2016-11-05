#ifndef BLOCKCPP
#define BLOCKCPP

#include "block.h"

template <typename T>
Array<T>::Block::Block(const size_t &n_capacity)
{
    m_size = 0;
    m_capacity = n_capacity;
    m_data = new T[m_capacity];
}

template <typename T>
Array<T>::Block::Block(const Block &other):
    m_size(other.m_size), m_capacity(other.m_capacity)
{
    m_data = new T[m_capacity];
    for(int i = 0; i < m_size; ++i)
        m_data[i] = other[i];
}

template <typename T>
typename Array<T>::Block &Array<T>::Block::operator=(const Block &other)
{
    if(m_data)
        delete []m_data;
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_data = new T[m_capacity];
    for(int i = 0; i < m_size; ++i)
        m_data[i] = other[i];
}

template <typename T>
typename Array<T>::Block &Array<T>::Block::operator=(Block &&other)
{
    if(m_data)
        delete []m_data;
    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    other.m_data = nullptr;
    return *this;
}

template <typename T>
Array<T>::Block::~Block()
{
    if(m_data)
        delete []m_data;
}

template <typename T>
bool Array<T>::Block::empty()
{
    return m_size < m_capacity;
}

template <typename T>
double Array<T>::Block::m_ratio = DEFAULT_RATIO;

template <typename T>
void Array<T>::Block::push_back(T new_data)
{
    m_data[m_size] = new_data;
    ++m_size;
}

template <typename T>
T &Array<T>::Block::operator[](const size_t &n)
{
    assert(n <= m_size);
    return m_data[n];
}

template <typename T>
T Array<T>::Block::operator[](const size_t &n) const
{
    assert(n <= m_size);
    return m_data[n];
}

template <typename T>
size_t Array<T>::Block::size()
{
    return m_size;
}

template <typename T>
void Array<T>::Block::print_all()
{
    for(int i = 0; i < m_size; ++i)
        std::cout << m_data[i] << ' ';
}

template <typename T>
void Array<T>::Block::pop_back()
{
    --m_size;
}

template <typename T>
void Array<T>::Block::erase(const size_t &N)
{
    for(int i = N; i < m_size - 1; ++i)
        m_data[i] = m_data[i + 1];
    --m_size;
}

template <typename T>
void Array<T>::Block::insert(const size_t &N, const T &new_data)
{
    for(size_t i = m_size; i > N; --i)
        m_data[i] = m_data[i - 1];
    m_data[N] = new_data;
    ++m_size;
}

#endif
