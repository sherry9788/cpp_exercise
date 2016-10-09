#ifndef FRAC
#define FRAC

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using std::cout;
using std::endl;

enum sign { Positive = 1, Negative = 0 };

// This is a fraction class
class frac
{
public:
	// function
    // default constructor
	frac() = default;
    
    // constructor using two ints
	frac(int n_numerator, int n_denominator);
    
    // copy constructor
	frac(const frac& n_frac);
    
    // asignment constructor
	frac &operator=(const frac& n_frac);

    // destructor
	~frac() = default;
    
    // factorize the fraction
	bool trim();
    
    // return the numerator
	const int &numerator() const;
    
    // return the denominator
	const int &denominator() const;
    
    // if the fraction is positive, return true, else return false
	bool ispositive() const;
    
    // inverse the fraction
	frac operator-();
    
    // return the absolute value of the fraction
	frac abs() const;

    // some overlode function
	void operator+=(const frac &n_frac);

	void operator-=(const frac &n_frac);

	void operator*=(const frac &n_frac);

	void operator/=(const frac &n_frac);

	void operator+=(const int &n_int);

	void operator-=(const int &n_int);

	void operator*=(const int &n_int);

	void operator/=(const int &n_int);

private:
	// data
	bool m_sign = Positive;    // sign
	int m_denominator = 1;     // denominator
	int m_numerator = 0;       // numerator
};

// some overlode function
std::ostream &operator<<(std::ostream &out, const frac &n_frac);

std::istream &operator>>(std::istream &in, frac &n_frac);

frac operator+(const frac &n_frac_1, const frac &n_frac_2);

frac operator+(const frac &n_frac, const int &n_int);

frac operator+(const int &n_int, const frac &n_frac);

frac operator-(const frac &n_frac_1, const frac &n_frac_2);

frac operator-(const frac &n_frac, const int &n_int);

frac operator-(const int &n_int, const frac &n_frac);

frac operator*(const frac &n_frac_1, const frac &n_frac_2);

frac operator*(const int &n_int, const frac &n_frac);

frac operator*(const frac &n_frac, const int &n_int);

frac operator/(const frac &n_frac_1, const frac &n_frac_2);

frac operator/(const frac &n_frac, const int &n_int);

frac operator/(const int &n_int, const frac &n_frac);

bool operator<(const frac &n_frac_1, const frac &n_frac_2);

bool operator<(const int &n_int, const frac &n_frac);

bool operator<(const frac &n_frac, const int &n_int);

bool operator<=(const frac &n_frac_1, const frac &n_frac_2);

bool operator<=(const int &n_int, const frac &n_frac);

bool operator<=(const frac &n_frac, const int &n_int);

bool operator>(const frac &n_frac_1, const frac &n_frac_2);

bool operator>(const int &n_int, const frac &n_frac);

bool operator>(const frac &n_frac, const int &n_int);

bool operator>=(const frac &n_frac_1, const frac &n_frac_2);

bool operator>=(const int &n_int, const frac &n_frac);

bool operator>=(const frac &n_frac, const int &n_int);

bool operator==(const frac &n_frac_1, const frac &n_frac_2);

bool operator==(const int &n_int, const frac &n_frac);

bool operator==(const frac &n_frac, const int &n_int);

bool operator!=(const frac &n_frac_1, const frac &n_frac_2);

bool operator!=(const int &n_int, const frac &n_frac);

bool operator!=(const frac &n_frac, const int &n_int);

// a square function
double sqrt(frac m_frac);

#endif
