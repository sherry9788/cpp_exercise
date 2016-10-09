#include "frac.h"

frac::frac(int n_numerator, int n_denominator)
{
	assert(n_denominator != 0);
	m_denominator = n_denominator;
	m_numerator = n_numerator;
	trim();
}

frac::frac(const frac& n_frac)
{
	m_sign = n_frac.m_sign;
	m_denominator = n_frac.m_denominator;
	m_numerator = n_frac.m_numerator;
}

frac &frac::operator=(const frac& n_frac)
{
	m_sign = n_frac.m_sign;
	m_denominator = n_frac.m_denominator;
	m_numerator = n_frac.m_numerator;
	return *this;
}

bool frac::trim()
{
	bool is_changed = false;

	if ((double)m_numerator * (double)m_denominator < 0)
		m_sign = Negative;
	else
		m_sign = Positive;

	m_numerator = std::abs(m_numerator);
	m_denominator = std::abs(m_denominator);

	if (m_numerator == 0)
	{
		m_denominator = 1;
		return is_changed;
	}

	for (int i = 2; m_denominator != 1
		&& i <= m_numerator
		&& i <= m_denominator; ++i)
	{
		if (m_numerator % i == 0 && m_denominator % i == 0)
		{
			m_numerator /= i;
			m_denominator /= i;
			is_changed = true;
			i = 1;
		}
	}

	return is_changed;
}

const int &frac::numerator() const
{
	return m_numerator;
}

const int &frac::denominator() const
{
	return m_denominator;
}

bool frac::ispositive() const
{
	return m_sign;
}

frac frac::operator-()
{
	frac ret_frac(m_numerator, m_denominator);
	ret_frac.m_sign = !m_sign;
	return ret_frac;
}

frac frac::abs() const
{
	return frac(m_numerator, m_denominator);
}

std::ostream &operator<<(std::ostream &out, const frac &n_frac)
{
	if (!n_frac.ispositive())
		out << '-';
	if (n_frac.denominator() == 1)
	{
		out << n_frac.numerator();
	}
	else
		out << n_frac.numerator() << '/' << n_frac.denominator();
	return out;
}

std::istream &operator>>(std::istream &in, frac &n_frac)
{
    int up, down;
    in >> up >> down;
    n_frac = frac(up, down);
    return in;
}

frac operator+(const frac &n_frac_1, const frac &n_frac_2)
{
	if (n_frac_1.ispositive() && n_frac_2.ispositive())
		return frac(n_frac_1.numerator() * n_frac_2.denominator() +
			n_frac_1.denominator() * n_frac_2.numerator(),
			n_frac_1.denominator() * n_frac_2.denominator());
	else if (!n_frac_1.ispositive() && !n_frac_2.ispositive())
		return 0 - (n_frac_1.abs() + n_frac_2.abs());
	else if (n_frac_1.ispositive())
		return n_frac_1 - n_frac_2.abs();
	else
		return n_frac_2 - n_frac_1.abs();
}

frac operator+(const frac &n_frac, const int &n_int)
{
	return n_frac + frac(n_int, 1);
}

frac operator+(const int &n_int, const frac &n_frac)
{
	return n_frac + frac(n_int, 1);
}

frac operator-(const frac &n_frac_1, const frac &n_frac_2)
{
	if (n_frac_1.ispositive() && n_frac_2.ispositive())
		return frac(n_frac_1.numerator() * n_frac_2.denominator() -
			n_frac_1.denominator() * n_frac_2.numerator(),
			n_frac_1.denominator() * n_frac_2.denominator());
	else if (!n_frac_1.ispositive() && !n_frac_2.ispositive())
		return n_frac_2.abs() - n_frac_1.abs();
	else if (n_frac_1.ispositive())
		return n_frac_1 + n_frac_2.abs();
	else
		return 0 - (n_frac_1.abs() + n_frac_2);
}

frac operator-(const frac &n_frac, const int &n_int)
{
	return n_frac - frac(n_int, 1);
}

frac operator-(const int &n_int, const frac &n_frac)
{
	return frac(n_int, 1) - n_frac;
}

frac operator*(const frac &n_frac_1, const frac &n_frac_2)
{
	if ((n_frac_1.ispositive() && n_frac_2.ispositive())
		|| (!n_frac_1.ispositive() && !n_frac_2.ispositive()))
		return frac(n_frac_1.numerator() * n_frac_2.numerator(),
			n_frac_1.denominator() * n_frac_2.denominator());
	else
		return 0 - frac(n_frac_1.numerator() * n_frac_2.numerator(),
			n_frac_1.denominator() * n_frac_2.denominator());
}

frac operator*(const int &n_int, const frac &n_frac)
{
	return n_frac * frac(n_int, 1);
}

frac operator*(const frac &n_frac, const int &n_int)
{
	return n_frac * frac(n_int, 1);
}

frac operator/(const frac &n_frac_1, const frac &n_frac_2)
{
	if (n_frac_2.ispositive())
		return n_frac_1 * frac(n_frac_2.denominator(), n_frac_2.numerator());
	else
		return  0 - (n_frac_1 * frac(n_frac_2.denominator(), n_frac_2.numerator()));
}

frac operator/(const frac &n_frac, const int &n_int)
{
	return n_frac / frac(n_int, 1);
}

frac operator/(const int &n_int, const frac &n_frac)
{
	return frac(n_int, 1) / n_frac;
}

bool operator<(const frac &n_frac_1, const frac &n_frac_2)
{
	double d_1 = n_frac_1.numerator() / (double)n_frac_1.denominator();
	if (!n_frac_1.ispositive())
		d_1 = -d_1;

	double d_2 = n_frac_2.numerator() / (double)n_frac_2.denominator();
	if (!n_frac_2.ispositive())
		d_2 = -d_2;

	if (d_1 < d_2)
		return true;

	return false;
}

bool operator<(const int &n_int, const frac &n_frac)
{
	return frac(n_int, 1) < n_frac;
}

bool operator<(const frac &n_frac, const int &n_int)
{
	return n_frac < frac(n_int, 1);
}

bool operator<=(const frac &n_frac_1, const frac &n_frac_2)
{
	double d_1 = n_frac_1.numerator() / (double)n_frac_1.denominator();
	if (!n_frac_1.ispositive())
		d_1 = -d_1;

	double d_2 = n_frac_2.numerator() / (double)n_frac_2.denominator();
	if (!n_frac_2.ispositive())
		d_2 = -d_2;

	if (d_1 <= d_2)
		return true;

	return false;
}

bool operator<=(const int &n_int, const frac &n_frac)
{
	return frac(n_int, 1) <= n_frac;
}

bool operator<=(const frac &n_frac, const int &n_int)
{
	return n_frac <= frac(n_int, 1);
}

bool operator>(const frac &n_frac_1, const frac &n_frac_2)
{
	double d_1 = n_frac_1.numerator() / (double)n_frac_1.denominator();
	if (!n_frac_1.ispositive())
		d_1 = -d_1;

	double d_2 = n_frac_2.numerator() / (double)n_frac_2.denominator();
	if (!n_frac_2.ispositive())
		d_2 = -d_2;

	if (d_1 > d_2)
		return true;

	return false;
}

bool operator>(const int &n_int, const frac &n_frac)
{
	return frac(n_int, 1) > n_frac;
}

bool operator>(const frac &n_frac, const int &n_int)
{
	return n_frac > frac(n_int, 1);
}

bool operator>=(const frac &n_frac_1, const frac &n_frac_2)
{
	double d_1 = n_frac_1.numerator() / (double)n_frac_1.denominator();
	if (!n_frac_1.ispositive())
		d_1 = -d_1;

	double d_2 = n_frac_2.numerator() / (double)n_frac_2.denominator();
	if (!n_frac_2.ispositive())
		d_2 = -d_2;

	if (d_1 >= d_2)
		return true;

	return false;
}

bool operator>=(const int &n_int, const frac &n_frac)
{
	return frac(n_int, 1) >= n_frac;
}

bool operator>=(const frac &n_frac, const int &n_int)
{
	return n_frac >= frac(n_int, 1);
}

bool operator==(const frac &n_frac_1, const frac &n_frac_2)
{
	double d_1 = n_frac_1.numerator() / (double)n_frac_1.denominator();
	if (!n_frac_1.ispositive())
		d_1 = -d_1;

	double d_2 = n_frac_2.numerator() / (double)n_frac_2.denominator();
	if (!n_frac_2.ispositive())
		d_2 = -d_2;

	if (d_1 == d_2)
		return true;

	return false;
}

bool operator==(const int &n_int, const frac &n_frac)
{
	return frac(n_int, 1) == n_frac;
}

bool operator==(const frac &n_frac, const int &n_int)
{
	return n_frac == frac(n_int, 1);
}

bool operator!=(const frac &n_frac_1, const frac &n_frac_2)
{
	double d_1 = n_frac_1.numerator() / (double)n_frac_1.denominator();
	if (!n_frac_1.ispositive())
		d_1 = -d_1;

	double d_2 = n_frac_2.numerator() / (double)n_frac_2.denominator();
	if (!n_frac_2.ispositive())
		d_2 = -d_2;

	if (d_1 != d_2)
		return true;

	return false;
}

bool operator!=(const int &n_int, const frac &n_frac)
{
	return frac(n_int, 1) != n_frac;
}

bool operator!=(const frac &n_frac, const int &n_int)
{
	return n_frac != frac(n_int, 1);
}

double sqrt(frac n_frac)
{
	return std::sqrt(n_frac.numerator()) / (double)std::sqrt(n_frac.denominator());
}

void frac::operator+=(const frac &n_frac)
{
	*this =  *this + n_frac;
}

void frac::operator-=(const frac &n_frac)
{
	*this = *this - n_frac;
}

void frac::operator*=(const frac &n_frac)
{
	*this = *this * n_frac;
}

void frac::operator/=(const frac &n_frac)
{
	*this = *this / n_frac;
}

void frac::operator+=(const int &n_int)
{
	*this = *this + n_int;
}

void frac::operator-=(const int &n_int)
{
	*this = *this - n_int;
}

void frac::operator*=(const int &n_int)
{
	*this = *this * n_int;
}

void frac::operator/=(const int &n_int)
{
	*this = *this / n_int;
}
