#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>
#include <cstdlib>
#include <limits>

struct Complex {
  Complex() = default;
  Complex(const Complex&) = default;
  explicit Complex(const double real);
  Complex(const double real, const double imaginary);

  Complex& operator = (const Complex&) = default;

  double re{ 0.0 };
  double im{ 0.0 };

  // bool
  bool operator==(const Complex& x) const;
  bool operator!=(const Complex& x) const;

  Complex operator -() const;

  // arithmetic
  Complex& operator+=(const Complex& rhs);
  Complex& operator+=(const double rhs);

  Complex& operator-=(const Complex& rhs);
  Complex& operator-=(const double rhs);

  Complex& operator*=(const Complex& rhs);
  Complex& operator*=(const double rhs);

  Complex& operator/=(const Complex& rhs);
  Complex& operator/=(const double rhs);

  std::ostream& writeTo(std::ostream& ostrm) const;
  std::istream& readFrom(std::istream& istrm);

  static const char leftBrace{ '{' };
  static const char separator{ ',' };
  static const char rightBrace{ '}' };

  ~Complex() = default;
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator+(const Complex& lhs, const double rhs);
Complex operator+(const double lhs, const Complex& rhs);

Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex & lhs, const double rhs);
Complex operator-(const double lhs, const Complex& rhs);

Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const double rhs);
Complex operator*(const double lhs, const Complex& rhs);

Complex operator/(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const double rhs);
Complex operator/(const double lhs, const Complex& rhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs) {
  return rhs.writeTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Complex& rhs) {
  return rhs.readFrom(istrm);
}

void testParse(const std::string& str);

#endif
