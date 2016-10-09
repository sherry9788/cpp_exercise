#ifndef MATRIX
#define MATRIX

#include "row.h"

// This is a matrix class.
template <class T>
class Matrix
{
public:
	// function
    // default constructor
	Matrix<T>() = default;
    
    // constructor with a vector
	Matrix<T>(std::vector<std::vector<T> > n_data);
    
    // constructor with a istream
    Matrix<T>(std::istream& in);

    // constructor with an array
    Matrix<T>(int n_rows, int n_cols, T* n_data);

    // constructor with a list
    Matrix<T>(std::initializer_list<std::initializer_list<T> > n_data);
    
    // copy constructor
	Matrix<T>(const Matrix<T> &n_Matrix);

    // asignment function
	Matrix<T> &operator=(const Matrix<T> &n_Matrix);

    // return the row of n_num rows
	row<T> &operator[](int n_num);

    // destructor
	~Matrix<T>();
    
    // the power function
	Matrix<T> operator^(int num) const;

    // return the inverse of the matrix
	Matrix<T> inv() const;

    // return the coordinates of the max element of the matrix
	int *max_index() const;

    // return the value of the max element of the matrix
	T max() const;

    // return the sum of all elements of the matrix
	T sum() const;

    // return the transpose matrix of the matrix
	Matrix<T> transpose() const;

    // return the size of the matrix
	unsigned size() const;

    // return the number of rows of the matrix
	unsigned rows() const;

    // return the number of columns of the matrix
	unsigned cols() const;

    // return the value of the element in the given coordinates 
	T get(const unsigned i, const unsigned j) const;

    // return the determinant of the matrix
	T det() const;

    // return the elements in diaonose line of the matrix
	T *diag() const;

    // return the normal summary of the matrix
	double norm() const;

    // resize the matrix to a new form
	Matrix<T> resize(int sizeRow, int sizeCol);

    // swap i1 and i2 rows of the matrix
	void swaprows(int i1, int i2);

    // swap j1 and j2 cloumns of the matrix
	void swapcols(int i1, int i2);	

private:
	// data
	row<T> **m_rows = nullptr;  // pointer to the rows
	int m_num_rows = 0;         // the number of the rows
};

// return (-1)^(i)
inline int get_sign(int i);

// some overload functions
template <class T>
Matrix<T> operator+(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2);

template <class T>
Matrix<T> operator-(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2);

template <class T>
Matrix<T> operator*(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2);

template <class T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &n_matrix);

template <class T>
Matrix<T> operator*(const T &n_T, const Matrix<T> &n_matrix);

template <class T>
bool operator<(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2);

template <class T>
bool operator>(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2);

template <class T>
bool operator==(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2);

template <class T>
bool operator<=(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2);

template <class T>
bool operator>=(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2);

template <class T>
bool operator!=(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2);

template <class T>
Matrix<T>::Matrix(std::istream& in)
{
    std::cout << "Please type the number of rows..." << std::endl;
    unsigned rows = 0;
    in >> rows;
    std::cout << "Please type the number of columns..." << std::endl;
    unsigned cols = 0;
    in >> cols;
    std::vector<std::vector<T> > n_data;
    n_data.resize(rows);
    for(unsigned i = 0; i < rows; ++i)
        n_data[i].resize(cols);
    for(unsigned i = 0; i < rows; ++i)
        for(unsigned j = 0; j < cols; ++j)
        {
            in >> n_data[i][j];
        }
	if (n_data.size() == 0)
		return;

	m_num_rows = n_data.size();

	for (unsigned int i = 1; i < n_data.size(); ++i)
		assert(n_data[i].size() == n_data[i - 1].size());

	m_rows = new row<T>*[m_num_rows];
	for (int i = 0; i < m_num_rows; ++i)
		m_rows[i] = new row<T>(n_data[i]);
}

template <class T>
Matrix<T>::Matrix(std::vector<std::vector<T> > n_data)
{
	if (n_data.size() == 0)
		return;

	m_num_rows = n_data.size();

	for (unsigned int i = 1; i < n_data.size(); ++i)
		assert(n_data[i].size() == n_data[i - 1].size());

	m_rows = new row<T>*[m_num_rows];
	for (int i = 0; i < m_num_rows; ++i)
		m_rows[i] = new row<T>(n_data[i]);
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &n_Matrix)
{
	m_num_rows = n_Matrix.m_num_rows;
	m_rows = new row<T>*[m_num_rows];
	for (int i = 0; i < m_num_rows; ++i)
		m_rows[i] = new row<T>(*n_Matrix.m_rows[i]);
}

template <class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &n_Matrix)
{
	m_num_rows = n_Matrix.m_num_rows;
	m_rows = new row<T>*[m_num_rows];
	for (int i = 0; i < m_num_rows; ++i)
		m_rows[i] = new row<T>(*n_Matrix.m_rows[i]);
	return *this;
}

template <class T>
row<T> &Matrix<T>::operator[](int n_num)
{
	return *m_rows[n_num];
}

template <class T>
Matrix<T>::~Matrix<T>()
{
	for (int i = 0; i < m_num_rows; ++i)
		delete m_rows[i];
	delete m_rows;
}

template <class T>
T Matrix<T>::max() const
{
	if (m_num_rows == 0 || m_rows[0]->size() == 0)
		return T();
	T ret_max = (*m_rows)[0][0];
	for (int i = 0; i < m_num_rows; ++i)
	{
		for (int j = 0; j < m_rows[0]->size(); ++j)
		{
			if (ret_max < (*m_rows[i])[j])
				ret_max = (*m_rows[i])[j];
		}
	}
	return ret_max;
}

template <class T>
T Matrix<T>::sum() const
{
	T ret_sum = T();
	for (int i = 0; i < m_num_rows; ++i)
		ret_sum += m_rows[i]->sum();
	return ret_sum;
}

template <class T>
unsigned Matrix<T>::size() const
{
	return m_num_rows * m_rows[0]->size();
}

template <class T>
unsigned Matrix<T>::rows() const
{
	return m_num_rows;
}

template <class T>
unsigned Matrix<T>::cols() const
{
	return size() / rows();
}

template <class T>
Matrix<T> Matrix<T>::inv() const
{
	T n_det = det();
	assert(n_det != 0);
	std::vector<std::vector<T> > cofactor_vector;
	cofactor_vector.resize(cols());
	for (unsigned i = 0; i < rows(); ++i)
	{
		for (unsigned j = 0; j < cols(); ++j)
		{
			std::vector<std::vector<T> > tmp_matrix;
			tmp_matrix.resize(rows());
			for (unsigned i_inner = 0; i_inner < rows(); ++i_inner)
			{
				for (unsigned j_inner = 0; j_inner < cols(); ++j_inner)
				{
					if (i_inner != i && j_inner != j)
						tmp_matrix[i_inner].push_back(get(i_inner, j_inner));
				}
			}
			
			for (unsigned k = i; k < rows() - 1; ++k)
				tmp_matrix[k] = tmp_matrix[k + 1];

			tmp_matrix.resize(rows() - 1);

			cofactor_vector[i].push_back(get_sign(i + j) * Matrix<T>(tmp_matrix).det());
		}
	}

	Matrix<T> cofactor(cofactor_vector);
	Matrix<T> ret_matrix = ((1 / n_det) * cofactor).transpose();

	return ret_matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator^(int num) const
{
	assert(cols() == cols());
	std::vector<std::vector<T> > ret_matrix_vector;
	ret_matrix_vector.resize(rows());
	
	if (num == 0)
	{
		for (unsigned i = 0; i < rows(); ++i)
		{
			ret_matrix_vector[i].resize(rows());
			ret_matrix_vector[i][i] = frac(1, 0);
		}
		return Matrix<T>(ret_matrix_vector);
	}
	else if (num < 0)
	{
		for (unsigned i = 0; i < rows(); ++i)
		{
			for (unsigned j = 0; j < cols(); ++j)
			{
				ret_matrix_vector[i].push_back(get(i, j));
			}
		}
		Matrix<T> ret_matrix(ret_matrix_vector);
		ret_matrix = ret_matrix.inv();
		for (int i = 1; i < -num; ++i)
		{
			ret_matrix = ret_matrix * ret_matrix;
		}

		return ret_matrix;
	}
	else
	{
		for (unsigned i = 0; i < rows(); ++i)
		{
			for (unsigned j = 0; j < cols(); ++j)
			{
				ret_matrix_vector[i].push_back(get(i, j));
			}
		}
		Matrix<T> ret_matrix(ret_matrix_vector);
		for (int i = 1; i < num; ++i)
		{
			ret_matrix = ret_matrix * ret_matrix;
		}

		return ret_matrix;
	}

}

template <class T>
Matrix<T> Matrix<T>::transpose() const
{
	std::vector<std::vector<T> > ret_matrix_vector;
	ret_matrix_vector.resize(cols());
	for (unsigned i = 0; i < rows(); ++i)
	{
		for (unsigned j = 0; j < cols(); ++j)
		{
			ret_matrix_vector[j].push_back(get(i, j));
		}
	}
	return Matrix<T>(ret_matrix_vector);
}

template <class T>
T Matrix<T>::get(const unsigned i, const unsigned j) const
{
	return (*m_rows[i])[j];
}

template <class T>
T Matrix<T>::det() const
{
	assert(cols() == rows());

	if (cols() == 1)
	{
		return get(0, 0);
	}
	int sign = 1;
	T ret_det = T();
	for (unsigned i = 0; i < cols(); ++i)
	{
		std::vector<std::vector<T> > new_matrix_vector;
		new_matrix_vector.resize(rows() - 1);
		for (unsigned j = 1; j < rows(); ++j)
			for (unsigned k = 0; k < rows(); ++k)
				if (k != i)
					new_matrix_vector[j - 1].push_back(get(j, k));

		ret_det += Matrix<T>(new_matrix_vector).det() * sign * get(0, i);
		sign = -sign;
	}

	return ret_det;
}

template <class T>
Matrix<T> operator+(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2)
{
	assert(n_matrix_1.cols() == n_matrix_2.cols() 
		&& n_matrix_1.rows() == n_matrix_2.rows());

	std::vector<std::vector<T> > ret_matrix;
	ret_matrix.resize(n_matrix_1.rows());
	for (unsigned i = 0; i < n_matrix_1.rows(); ++i)
	{
		ret_matrix[i].resize(n_matrix_1.cols());
		for (unsigned j = 0; j < n_matrix_1.cols(); ++j)
		{
			ret_matrix[i][j] = n_matrix_1.get(i, j) + n_matrix_2.get(i, j);
		}
	}

	return Matrix<T>(ret_matrix);
}

template <class T>
Matrix<T> operator-(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2)
{
	assert(n_matrix_1.cols() == n_matrix_2.cols()
		&& n_matrix_1.rows() == n_matrix_2.rows());

	std::vector<std::vector<T> > ret_matrix;
	ret_matrix.resize(n_matrix_1.rows());
	for (unsigned i = 0; i < n_matrix_1.rows(); ++i)
	{
		ret_matrix[i].resize(n_matrix_1.cols());
		for (unsigned j = 0; j < n_matrix_1.cols(); ++j)
		{
			ret_matrix[i][j] = n_matrix_1.get(i, j) - n_matrix_2.get(i, j);
		}
	}

	return Matrix<T>(ret_matrix);
}

template <class T>
Matrix<T> operator*(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2)
{
	assert(n_matrix_1.cols() == n_matrix_2.rows());

	std::vector<std::vector<T> > ret_matrix;
	ret_matrix.resize(n_matrix_1.rows());
	for (unsigned i = 0; i < n_matrix_1.rows(); ++i)
	{
		ret_matrix[i].resize(n_matrix_2.cols());
		for (unsigned j = 0; j < n_matrix_2.cols(); ++j)
		{
			T each_element = T();
			for (unsigned k = 0; k < n_matrix_1.cols(); ++k)
			{
				each_element += n_matrix_1.get(i, k) * n_matrix_2.get(k, j);
			}
			ret_matrix[i][j] = each_element;
		}
	}

	return Matrix<T>(ret_matrix);
}

template <class T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &n_matrix)
{
	for (unsigned i = 0; i < n_matrix.rows(); ++i)
	{
		for (unsigned j = 0; j < n_matrix.cols(); ++j)
			out << n_matrix.get(i, j) << '\t';
		out << endl;
	}
	return out;
}

inline int get_sign(int i)
{
	return i % 2 == 0 ? 1 : -1;
}

template <class T>
Matrix<T> operator*(const T &n_T, const Matrix<T> &n_matrix)
{
	Matrix<T> ret_matrix = n_matrix;
	for (unsigned i = 0; i < n_matrix.rows(); ++i)
		for (unsigned j = 0; j < n_matrix.cols(); ++j)
			ret_matrix[i][j] *= n_T;
	return ret_matrix;
}

template <class T>
T *Matrix<T>::diag() const
{
	T *ret_arr = new T[rows()];
	for (unsigned i = 0; i < rows(); ++i)
	{
		ret_arr[i] = get(i, i);
	}

	return ret_arr;
}

template <class T>
double Matrix<T>::norm() const
{
	T ret_norm = T();
	for (unsigned i = 0; i < rows(); ++i)
	{
		for (unsigned j = 0; j < cols(); ++j)
		{
			ret_norm += get(i, j) * get(i, j);
		}
	}
	
	return sqrt(ret_norm);
}

template <class T>
int *Matrix<T>::max_index() const
{
	int *ret_index = new int[2];

	ret_index[0] = 0;
	ret_index[1] = 0;

	if (m_num_rows == 0 || m_rows[0]->size() == 0)
		return ret_index;

	T ret_max = (*m_rows)[0][0];
	for (int i = 0; i < m_num_rows; ++i)
	{
		for (int j = 0; j < m_rows[0]->size(); ++j)
		{
			if (ret_max < (*m_rows[i])[j])
			{
				ret_max = (*m_rows[i])[j];
				ret_index[0] = i;
				ret_index[1] = j;
			}
		}
	}
	return ret_index;
}

template <class T>
Matrix<T> Matrix<T>::resize(int sizerow, int sizeCol)
{
	assert(sizerow > 0 && sizeCol > 0);
	
	std::vector<T> old_matrix_vector;
	for (unsigned i = 0; i < rows(); ++i)
		for (unsigned j = 0; j < cols(); ++j)
			old_matrix_vector.push_back(get(i, j));

	std::vector<std::vector<T> > new_matrix_vector;
	new_matrix_vector.resize(old_matrix_vector.size() / sizeCol + 1);
	new_matrix_vector.resize(sizerow);
	for (unsigned i = 0; i < old_matrix_vector.size(); ++i)
	{
		new_matrix_vector[i / sizeCol].push_back(old_matrix_vector[i]);
	}

	new_matrix_vector.resize(sizerow);
	for (int i = 0; i < sizerow; ++i)
		new_matrix_vector[i].resize(sizeCol);

	return Matrix<T>(new_matrix_vector);
}

template <class T>
void Matrix<T>::swaprows(int i1, int i2)
{
	row<T> *tmp_row = m_rows[i1];
	m_rows[i1] = m_rows[i2];
	m_rows[i2] = tmp_row;
}

template <class T>
void Matrix<T>::swapcols(int j1, int j2)
{
	for (unsigned i = 0; i < rows(); ++i)
	{
		T tmp = get(i, j1);
		(*this)[i][j1] = (*this)[i][j2];
		(*this)[i][j2] = tmp;
	}
}

template <class T>
bool operator<(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2)
{
    for(unsigned i = 0; i < n_matrix_1.size() && i < n_matrix_2.size(); ++ i)
    {
        if(n_matrix_1[i / n_matrix_1.cols()][i % n_matrix_1.cols()] >
                n_matrix_2[i / n_matrix_2.cols()][i % n_matrix_2.cols()])
            return false;
        else if(n_matrix_1[i / n_matrix_1.cols()][i % n_matrix_1.cols()] <
                n_matrix_2[i / n_matrix_2.cols()][i % n_matrix_2.cols()])
            return true;
    }

    if(n_matrix_1.size() < n_matrix_2.size())
        return true;

    return false;
}

template <class T>
bool operator>(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2)
{
    for(unsigned i = 0; i < n_matrix_1.size() && i < n_matrix_2.size(); ++ i)
    {
        if(n_matrix_1[i / n_matrix_1.cols()][i % n_matrix_1.cols()] <
                n_matrix_2[i / n_matrix_2.cols()][i % n_matrix_2.cols()])
            return false;
        else if(n_matrix_1[i / n_matrix_1.cols()][i % n_matrix_1.cols()] >
                n_matrix_2[i / n_matrix_2.cols()][i % n_matrix_2.cols()])
            return true;
    }

    if(n_matrix_1.size() > n_matrix_2.size())
        return true;

    return false;
}

template <class T>
bool operator==(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2)
{
    return !(n_matrix_1 > n_matrix_2) && !(n_matrix_1 < n_matrix_2);
}

template <class T>
bool operator<=(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2)
{
    return n_matrix_1 < n_matrix_2 || n_matrix_1 == n_matrix_2;
}

template <class T>
bool operator>=(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2)
{
    return n_matrix_1 > n_matrix_2 || n_matrix_1 == n_matrix_2;
}

template <class T>
bool operator!=(const Matrix<T> &n_matrix_1, const Matrix<T> &n_matrix_2)
{
    return n_matrix_1 > n_matrix_2 || n_matrix_1 < n_matrix_2;
}

template <class T>
Matrix<T>::Matrix(int n_rows, int n_cols, T* n_data)
{
    std::vector<std::vector<T> > n_vector;
    n_vector.resize(n_rows);
    for(int i = 0; i < n_rows; ++i)
        n_vector[i].resize(n_cols);
    for(int i = 0; i < n_rows; ++i)
        for(int j = 0; j < n_cols; ++j)
            n_vector[i][j] = n_data[i * n_cols + j];
	if (n_vector.size() == 0)
		return;

	m_num_rows = n_vector.size();

	for (unsigned int i = 1; i < n_vector.size(); ++i)
		assert(n_vector[i].size() == n_vector[i - 1].size());

	m_rows = new row<T>*[m_num_rows];
	for (int i = 0; i < m_num_rows; ++i)
		m_rows[i] = new row<T>(n_vector[i]);
}

template <class T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T> > n_data)
{
    std::vector<std::vector<T> > n_vector;
    n_vector.resize(n_data.size());
    auto p = n_data.begin();
    for(unsigned i = 0; i < n_vector.size(); ++i)
    {
        n_vector[i] = std::vector<T>(*p);
        ++p;
    }

	if (n_vector.size() == 0)
		return;

	m_num_rows = n_vector.size();

	for (unsigned int i = 1; i < n_vector.size(); ++i)
		assert(n_vector[i].size() == n_vector[i - 1].size());

	m_rows = new row<T>*[m_num_rows];
	for (int i = 0; i < m_num_rows; ++i)
		m_rows[i] = new row<T>(n_vector[i]);
}

#endif
