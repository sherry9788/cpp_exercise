#ifndef BLOCKLIST
#define BLOCKLIST

#include "block.h"

template <typename T>
struct Array<T>::BlockList
{
    friend class Array<T>;
    public:
        using pBlock = Block*;
        size_t size() const;
        ~BlockList();
        BlockList(size_t n_capacity = DEFAULT_TABLE_SIZE, 
                size_t n_block_capacity = DEFAULT_LENGTH);
        int push_back(T new_data);
        T &operator[](size_t n);
        int pop_back();
        void print_all(int command);
        int insert(size_t N, T new_data);
        int erase(size_t N);

        BlockList(const BlockList &other);
        BlockList(BlockList &&other) = default;
        BlockList &operator=(const BlockList &other);
        BlockList &operator=(BlockList &&other);

        T get(size_t N) const;

    private:
        size_t m_table_size;
        size_t m_table_capacity;
        size_t m_size;
        size_t m_default_block_size;

        pBlock *m_table = nullptr;
};

#include "blocklist.cpp.h"

#endif 
