#ifndef BLOCKLISTCPP
#define BLOCKLISTCPP

#include "blocklist.h"

template <typename T>
Array<T>::BlockList::~BlockList()
{
    if(m_table)
    {
        for(int i = 0; i < m_table_size; ++i)
            delete m_table[i];

        delete []m_table;
    }
}

template <typename T>
Array<T>::BlockList::BlockList(size_t n_capacity,
        size_t n_block_capacity)
{
    m_table_size = 1;
    m_size = 0;
    m_table_capacity = n_capacity;
    m_table = new pBlock[n_capacity];
    m_default_block_size = n_block_capacity;
    if(!m_table)
        std::cerr << "can't assign memory to m_table" << std::endl;
    m_table[0] = new Block(n_block_capacity);
    if(!m_table[0])
        std::cerr << "can't assign memory to m_table[0]" << std::endl;
}

template <typename T>
Array<T>::BlockList::BlockList(const BlockList &other):
    m_table_size(other.m_table_size), m_size(other.m_size),
    m_table_capacity(other.m_table_capacity),
    m_default_block_size(other.m_default_block_size)
{
    m_table = new pBlock[m_table_capacity];
    for(size_t i = 0; i < m_table_size; ++i)
        m_table[i] = new Block(*other.m_table[i]);
}

template <typename T>
typename Array<T>::BlockList &Array<T>::BlockList::operator=(const BlockList &other)
{
    if(m_table)
    {
        for(int i = 0; i < m_table_size; ++i)
            delete m_table[i];
        delete []m_table;
    }
    m_table_size = other.m_table_size;
    m_table_capacity = other.m_table_capacity;
    m_default_block_size = other.m_default_block_size;
    m_size = other.m_size;
    m_table = new pBlock[m_table_capacity];
    for(size_t i = 0; i < m_table_size; ++i)
        m_table[i] = new Block(*other.m_table[i]);
}

template <typename T>
typename Array<T>::BlockList &Array<T>::BlockList::operator=(BlockList &&other)
{
    if(m_table)
    {
        for(int i = 0; i < m_table_size; ++i)
            delete m_table[i];
        delete []m_table;
    }
    m_table = other.m_table;
    m_table_size = other.m_table_size;
    m_table_capacity = other.m_table_capacity;
    m_default_block_size = other.m_default_block_size;
    m_size = other.m_size;

    other.m_table = nullptr;
    return *this;
}

template <typename T>
int Array<T>::BlockList::push_back(T new_data)
{
    ++m_size;
    if(m_table[m_table_size - 1]->empty())
    {   
        m_table[m_table_size - 1]->push_back(new_data);
        return BLOCK_CHANGED;
    }
    else
    {
        if(m_table_size < m_table_capacity)
        {
            m_table[m_table_size] = new Block(m_default_block_size);
            if(!m_table[m_table_size])
                std::cerr << "can't assign memory to m_table[" << 
                    m_table_size << "]" << std::endl;
            m_table[m_table_size]->push_back(new_data);
            ++m_table_size;
        }
        else
        {
            pBlock *tmp_table = new pBlock[(size_t)(m_table_capacity *
                    (1 + DEFAULT_RATIO))];
            if(!tmp_table)
                std::cerr << "can't assign memory to tmp_table" << std::endl;
            for(int i = 0; i < m_table_size; ++i)
            {
                tmp_table[i] = m_table[i];
            }
            delete []m_table;
            m_table = tmp_table;
            m_table_capacity *= (1 + DEFAULT_RATIO);
            m_table[m_table_size] = new Block(m_default_block_size);
            if(!m_table[m_table_size])
                std::cerr << "can't assign memory to m_table[" << 
                    m_table_size << "]" << std::endl;
            m_table[m_table_size]->push_back(new_data);
            ++m_table_size;
        }
        return TABLE_CHANGED;
    }
}

template <typename T>
T &Array<T>::BlockList::operator[](size_t n)
{
    assert(n <= size());
    int i = 0;
    while(n >= m_table[i]->size())
    {
        n -= m_table[i]->size();
        ++i;
    }
    return (*m_table[i])[n];
}

template <typename T>
size_t Array<T>::BlockList::size() const
{
    return m_size;
}

template <typename T>
void Array<T>::BlockList::print_all(int command)
{
    if(command == WITH_DATA)
    {
        for(int i = 0; i < m_table_size; ++i)
        {
            std::cout << "Block # " << i << ":" << std::endl;
            m_table[i]->print_all();
            std::cout << std::endl;
        }
    }
    else
    {
        for(int i = 0; i < m_table_size; ++i)
        {
            std::cout << "Block # " << i << ":";
            std::cout << m_table[i]->size() << std::endl;
        }
    }
}

template <typename T>
int Array<T>::BlockList::pop_back()
{
    if(m_table[m_table_size - 1]->size() == 1)
    {
        delete m_table[m_table_size - 1];
        --m_size;
        --m_table_size;
        return TABLE_CHANGED;
    }
    else
    {
        m_table[m_table_size - 1]->pop_back();
        --m_size;
        return BLOCK_CHANGED;
    }
}

template <typename T>
int Array<T>::BlockList::insert(size_t N, T new_data)
{
    ++m_size;
    int i = 0;
    while(N > m_table[i]->size())
    {
        ++i;
        N -= m_table[i]->size();
    }

    if(m_table[i]->empty())
    {
        m_table[i]->insert(N, new_data);
        return BLOCK_CHANGED;
    }
    else
    {
        Block *tmp_block = new Block((size_t)(m_table[i]->size() 
                    * Block::m_ratio));
        for(int j = 0; j < m_table[i]->size(); ++j)
            tmp_block->push_back((*m_table[i])[j]);
        delete m_table[i];
        m_table[i] = tmp_block;
        m_table[i]->insert(N, new_data);
        return TABLE_CHANGED;
    }
}

template <typename T>
int Array<T>::BlockList::erase(size_t N)
{
    --m_size;
    int i = 0;
    while(N > m_table[i]->size())
    {
        ++i;
        N -= m_table[i]->size();
    }

    if(N != 0)
    {
        m_table[i]->erase(N);
        return BLOCK_CHANGED;
    }
    else
    {
        delete m_table[i];
        for(int i = i; i < m_table_size - 1; ++i)
            m_table[i] = m_table[i + 1];
        --m_table_size;
        return TABLE_CHANGED;
    }
}

template <typename T>
T Array<T>::BlockList::get(size_t N) const
{
    assert(N <= size());
    int i = 0;
    while(N >= m_table[i]->size())
    {
        N -= m_table[i]->size();
        ++i;
    }
    return m_table[i]->get(N);
}

#endif
