#ifndef BLOCK
#define BLOCK

#include "array.h"

template <typename T>
struct Array<T>::Block
{
    friend struct Array<T>::iterator;
    public:
        Block(const size_t &n_capacity = DEFAULT_LENGTH);
        bool empty();
        void push_back(T new_data);
        T &operator[](const size_t &n);
        T operator[](const size_t &n) const;
        size_t size();
        void pop_back();
        void print_all();
        void erase(const size_t &N);
        void insert(const size_t &N, const T &new_data);
        ~Block();

        Block &operator=(const Block &other);
        Block(const Block &other);
        Block(Block &&other) = default;
        Block &operator=(Block &&other);

        static double m_ratio;

    private:
        size_t m_capacity;
        size_t m_size;
        T *m_data = nullptr;

};

#include "block.cpp.h"

#endif
