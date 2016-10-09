#ifndef ROW
#define ROW

#include "frac.h"

// the row of a matrix
template <class T>
class row
{
public:
	// function
    // default constructor
	row<T>() = default;

    // constructor with a vector
	row<T>(std::vector<T> n_data);

    // copy constructor
	row<T>(const row<T>& n_row);

    // assignment function
	row<T> &operator=(const row<T>& n_row);

    // destructor
	~row<T>();

    // return m_data[n_num]
	T &operator[](int n_num);

    // return the summary of the row
	T sum() const;

    // return the max element of the row
	T max() const;

    // return the size of the row
	int size() const;

private:
	//data
	T* m_data = nullptr;   // data
	int m_size = 0;        // the size of the data
};

template <class T>
row<T>::row(std::vector<T> n_data)
{
	m_size = n_data.size();
	m_data = new T[m_size];
	for (int i = 0; i < m_size; ++i)
	{
		m_data[i] = n_data[i];
	}
}

template <class T>
row<T>::row(const row<T>& n_row)
{
	m_size = n_row.m_size;
	m_data = new T[m_size];
	for (int i = 0; i < m_size; ++i)
	{
		m_data[i] = n_row.m_data[i];
	}
}

template <class T>
row<T> &row<T>::operator=(const row<T>& n_row)
{
	m_size = n_row.m_size;
	m_data = new T[m_size];
	for (int i = 0; i < m_size; ++i)
	{
		m_data[i] = n_row.m_data[i];
	}
	return *this;
}

template <class T>
T &row<T>::operator[](int n_num)
{
	return m_data[n_num];
}

template <class T>
row<T>::~row<T>()
{
	delete m_data;
}

template <class T>
T row<T>::sum() const
{
	T ret_sum = T();
	for (int i = 0; i < m_size; ++i)
		ret_sum += m_data[i];
	return ret_sum;
}

template <class T>
T row<T>::max() const
{
	if (m_size == 0)
		return T();

	T ret_max = m_data[0];
	for (int i = 0; i < m_size; ++i)
		if (ret_max < m_data[i])
			ret_max = m_data[i];

	return ret_max;
}

template <class T>
int row<T>::size() const
{
	return m_size;
}

#endif
