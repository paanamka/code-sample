#include "rational.hpp"

#include <sstream>

/* std::istream& operator >> (std::istream& istrm, Rational& r) {
	char read_separator (0);
	int64_t read_num (0);
	int64_t read_den (0);

	istrm >> read_num >> read_separator >> read_den;

	if (!istrm.good()) {
		return istrm;
	}

	if (read_separator == r.separator && read_den != 0) {
		r.num_ = read_num;
		r.den_ = read_den;
	}
	else {
		istrm.setstate(std::ios_base::failbit);
	}
	return istrm;
} */

/* std::ostream& operator << (std::ostream& ostrm, const Rational& r) {
	return ostrm << r.num() << r.separator << r.den();
} */


Rational::Rational(const int64_t number) 
	:num_ (number) , den_ (1){}

Rational::Rational(const int64_t number, const int64_t denominator) {
	if (denominator == 0) {
		throw std::invalid_argument("zero denominator");
	}
	else if (denominator < 0) {
		num_ = number * (-1);
		den_ = denominator * (-1);
	}
	else {
		num_ = number;
		den_ = denominator;
	}
	reduction(*this);
}

bool Rational::operator == (const Rational& other) const {
	return ((num_ == other.num()) && (den_ == other.den()));
}

bool Rational::operator != (const Rational& other) const {
	return !operator==(other);
}

Rational& Rational::reduction(Rational& r) {
	int64_t number = r.num();
	int64_t denominator = r.den();

	int64_t m = std::min(number, denominator);
	int64_t M = std::max(number, denominator);

	for (int i = std::abs(M); i > 0; --i) {
		if ((number % i == 0) && (denominator % i == 0)) {
			number /= i;
			denominator /= i;
		}
	}
	if (denominator < 0) {
		r.num_ = number * (-1);
		r.den_ = denominator * (-1);
	}
	else {
		r.num_ = number;
		r.den_ = denominator;
	}
	return r;
}


Rational Rational::operator-() const {
	Rational neg(-(*this).num(), (*this).den());
	return neg;
}

Rational& Rational::operator += (const Rational& other) {
	int64_t ch = other.num();

	if (den_ != other.den()) {
		ch *= den_;
		num_ *= other.den();
		den_ *= other.den();
		num_ += ch;
		reduction(*this);
		return *this;
	}
	else {
		num_ += ch;
		reduction(*this);
		return *this;
	}
}

Rational& Rational::operator += (const int64_t other) {
	int64_t ch = other * den_;
	num_ += ch;
	reduction(*this);
	return *this;
}

Rational& Rational::operator -= (const Rational& other) {
	*this += (-other);
	reduction(*this);
	return *this;
}

Rational& Rational::operator -= (const int64_t other) {
	int64_t ch = other * den_;
	num_ -= ch;
	reduction(*this);
	return *this;
}

Rational& Rational::operator *= (const Rational& other) {
	num_ *= other.num();
	den_ *= other.den();
	reduction(*this);
	return *this;
}

Rational& Rational::operator *= (const int64_t other) {
	num_ *= other;
	reduction(*this);
	return *this;
}

Rational& Rational::operator /= (const Rational& other) {
	if (other.num() == 0) {
		throw std::invalid_argument("division by zero");
	}
	num_ *= other.den();
	den_ *= other.num();

	reduction(*this);
	return *this;
}

Rational& Rational::operator /= (const int64_t other) {
	if (other == 0) {
		throw std::invalid_argument("division by zero");
	}
	den_ *= other;
	reduction(*this);
	return *this;
}


Rational operator+(const Rational& lhs, const Rational& rhs) {
	Rational result = lhs;
	return result += rhs;
}

Rational operator+(const Rational& lhs, const int64_t rhs) {
	Rational result = lhs;
	return result += rhs;
}

Rational operator+(const int64_t lhs, const Rational& rhs) {
	return Rational(lhs) += rhs;
}


Rational operator-(const Rational& lhs, const Rational& rhs) {
	Rational result = lhs;
	return result -= rhs;
}

Rational operator-(const Rational& lhs, const int64_t rhs) {
	Rational result = lhs;
	return result -= rhs;
}

Rational operator-(const int64_t lhs, const Rational& rhs) {
	return Rational(lhs) -= rhs;
}


Rational operator*(const Rational& lhs, const Rational& rhs) {
	Rational result = lhs;
	return result *= rhs;
}

Rational operator*(const Rational& lhs, const int64_t rhs) {
	Rational result = lhs;
	return result *= rhs;
}

Rational operator*(const int64_t lhs, const Rational& rhs) {
	return Rational(lhs) *= rhs;
}


Rational operator/(const Rational& lhs, const Rational& rhs) {
	if (rhs.num() == 0) {
		throw std::invalid_argument("division by zero");
	}
	Rational result = lhs;
	return result /= rhs;
}

Rational operator/(const Rational& lhs, const int64_t rhs) {
	if (rhs == 0) {
		throw std::invalid_argument("division by zero");
	}
	Rational result = lhs;
	return result /= rhs;
}

/* std::ostream& Rational::writeTo(std::ostream& ostrm) const {
	ostrm << num_ << separator << den_;
	return ostrm;
} */


/* Rational& Rational::readFrom(std::istream& istrm) {
	//int number(0);
	int denominator(1);
	char slash(0);
	Rational n;

	istrm >> number >> slash >> denominator;
	if (istrm.good()) {
		if (Rational::separator == slash) {
			n = Rational(number, denominator);
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}

	return n;
} */

std::istream& Rational::readFrom(std::istream& istrm) noexcept {
	int64_t number(0);
	char separator(0);
	int64_t denominator(0);
	istrm >> number;
	istrm.get(separator);
	int64_t trash = istrm.peek();
	istrm >> denominator;
	if (!istrm || trash > '9' || trash < '0') {
		istrm.setstate(std::ios_base::failbit);
		return istrm;
	}
	if (istrm.good() || istrm.eof()) {
		if ('/' == separator && denominator != 0) {
			*this = Rational(number, denominator);
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}


std::ostream& Rational::writeTo(std::ostream& ostrm) const noexcept {
	ostrm << num_ << '/' << den_;
	return ostrm;
}