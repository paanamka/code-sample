#include <sstream>
#include <cstdlib>
#include <limits>
#include "complex.hpp"

Complex::Complex(const double real)
  : Complex(real, 0.0){}

Complex::Complex(const double real, const double imaginary)
  : re(real), im(imaginary){}

bool Complex::operator==(const Complex& x) const {
  return ((std::abs(re - x.re) <= 2 * std::numeric_limits<double>::epsilon()) && (std::abs(im - x.im) <= 2 * std::numeric_limits<double>::epsilon()));
}

bool Complex::operator!=(const Complex& x) const {
  return !operator==(x);
}

Complex Complex::operator -() const {
  return Complex(-re, -im);
}

Complex& Complex::operator+=(const Complex& rhs) {
  re += rhs.re;
  im += rhs.im;
  return *this;
}

Complex& Complex::operator+=(const double rhs) {
  re += rhs;
  return *this;
}

Complex& Complex::operator-=(const Complex& rhs) {
  re -= rhs.re;
  im -= rhs.im;
  return *this;
}

Complex& Complex::operator-=(const double rhs) {
  re -= rhs;
  return *this;
}


Complex& Complex::operator*=(const Complex& rhs) {
  double re_ = re;
  double im_ = im;
  re = re_ * rhs.re - im_ * rhs.im;
  im = im_ * rhs.re + re_ * rhs.im;
  return *this;
}

Complex& Complex::operator*=(const double rhs) {
  return (*this *= Complex(rhs));
}

Complex& Complex::operator/=(const Complex& rhs) {
  if (rhs == Complex(0.0, 0.0)) {
    throw std::invalid_argument("forbidden operation");
  }
  if (rhs.re * rhs.re + rhs.im * rhs.im == 0) {
    throw std::invalid_argument("zero denominator");
  }
  double re_ = re;
  double im_ = im;
  re = (re_ * rhs.re + im_ * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
  im = (im_ * rhs.re - re_ * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
  return *this;
}

Complex& Complex::operator /=(const double rhs) {
  return (*this /= Complex(rhs));
}


Complex operator+(const Complex& lhs, const Complex& rhs) {
  Complex result = lhs;
  return result += rhs;
}

Complex operator+(const Complex& lhs, const double rhs) {
  Complex result = lhs;
  return result += Complex(rhs);
}

Complex operator+(const double lhs, const Complex& rhs) {
  return Complex(lhs) += rhs;
}


Complex operator-(const Complex& lhs, const Complex& rhs) {
  Complex result = lhs;
  return result -= rhs;
}

Complex operator-(const Complex& lhs, const double rhs) {
  Complex result = lhs;
  return result -= Complex(rhs);
}

Complex operator-(const double lhs, const Complex& rhs) {
  return Complex(lhs) -= rhs;
}


Complex operator*(const Complex& lhs, const Complex& rhs) {
  Complex result;

  result.re = lhs.re * rhs.re - lhs.im * rhs.im;
  result.im = lhs.re * rhs.im + lhs.im * rhs.re;
  return result;
}

Complex operator*(const Complex& lhs, const double rhs) {
  Complex result = lhs;
  return (result *= Complex(rhs));
}

Complex operator*(const double lhs, const Complex& rhs) {
  return (Complex(lhs) *= rhs);
}


Complex operator/(const Complex& lhs, const Complex& rhs) {
  if (rhs == Complex(0.0, 0.0)) {
    throw std::invalid_argument("zero denominator");
  }

  if (rhs.re * rhs.re + rhs.im * rhs.im == 0) {
    throw std::invalid_argument("zero denominator");
  } 

  Complex result = lhs;
  return (result /= rhs);
}

Complex operator/(const Complex& lhs, const double rhs) {
  Complex result = lhs;
  return result /= rhs;
}

Complex operator/(const double lhs, const Complex& rhs) {
  if (rhs == Complex(0.0)) {
    throw std::invalid_argument("zero denominator");
  }

  if (rhs.re * rhs.re + rhs.im * rhs.im == 0) {
    throw std::invalid_argument("zero denominator");
  }

  Complex result;
  
  result.re = (lhs * rhs.re) / (rhs.re * rhs.re + rhs.im * rhs.im);
  result.im = (-lhs * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);

  return result;
}

std::ostream& Complex::writeTo(std::ostream& ostrm) const {
  ostrm << leftBrace << re << separator << im << rightBrace;
  return ostrm;
}

std::istream& Complex::readFrom(std::istream& istrm) {
  char leftBrace(0);
  double real(0.0);
  char comma(0);
  double imaganary(0.0);
  char rightBrace(0);

  istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;

  if (istrm.good()) {
    if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma) && (Complex::rightBrace == rightBrace)) {
      re = real;
      im = imaganary;
    }
    else {
      istrm.setstate(std::ios_base::failbit);
    }
  }
  return istrm;
}
