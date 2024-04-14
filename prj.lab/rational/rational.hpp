#pragma once

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <sstream>


class Rational {
public:
	//конструктор по умолчанию
	Rational() = default;

	//конструктор копирования
	Rational(const int64_t number);
	Rational(const int64_t number, const int64_t denominator);

	//сравнение
	bool operator ==(const Rational& other) const;
	bool operator !=(const Rational& other) const;

	//сокращение
	Rational& reduction(Rational& r);

	//арифметика
	Rational operator-() const;

	Rational& operator += (const Rational& other);
	Rational& operator += (const int64_t other);

	Rational& operator -= (const Rational& other);
	Rational& operator -= (const int64_t other);

	Rational& operator *= (const Rational& other);
	Rational& operator *= (const int64_t other);

	Rational& operator /= (const Rational& other);
	Rational& operator /= (const int64_t other);

	int64_t num() const {
		return num_;
	}
	int64_t den() const {
		return den_;
	}

	std::ostream& writeTo(std::ostream& ostrm) const noexcept;
	std::istream& readFrom(std::istream& istrm) noexcept;

	// деструктор
	~Rational() = default;

private:
	int64_t num_ = 0;
	int64_t den_ = 1;
	static const char separator{ '/' };
};


inline std::istream& operator>>(std::istream& istrm, Rational& x) noexcept {
	return x.readFrom(istrm);
}

inline std::ostream& operator<<(std::ostream& ostrm, Rational& x) noexcept {
	return x.writeTo(ostrm);
}


Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator+(const Rational& lhs, const int64_t rhs);
Rational operator+(const int64_t lhs, const Rational& rhs);

Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const int64_t rhs);
Rational operator-(const int64_t lhs, const Rational& rhs);

Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const int64_t rhs);
Rational operator*(const int64_t lhs, const Rational& rhs);

Rational operator/(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const int64_t rhs);

#endif 