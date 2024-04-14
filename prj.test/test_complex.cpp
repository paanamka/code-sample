#include <sstream>
#include <iostream>
#include <complex/complex.hpp>

void testParse(const std::string& str) {
  std::string line = str;
  std::istringstream istream (line);
  Complex z;
  istream >> z;


  std::cout << "Test " << str << " += 2 -> " << (z += Complex(2.0)) << std::endl;
  z -= Complex(2.0);
  std::cout << "Test " << str << " -= 2 -> " << (z -= 2.0) << std::endl;
  z += Complex(2.0);
  std::cout << "Test " << str << " *= 2 -> " << (z *= 2.0) << std::endl;
  z /= Complex(2.0);
  std::cout << "Test " << str << " /= 2 -> " << (z /= Complex(2.0)) << std::endl;

  try {
    z /= 0.0;
  }
  catch (std::invalid_argument) {
    std::cout << "Test " << str << " /= 0 -> " << "Forbidden operation: division by zero" << std::endl;
  }
}


int main() {
  testParse("{8.9, 9}");
  testParse("{10.9, 9.1}");
  testParse("{12.9, 9.2}");

  std::cout << "\n";
  Complex x(1, 1);
  Complex y(1, 1);

  std::cout << "Test " << x << " + " << 2.1 << " = " << x + 2.1 << std::endl;
  std::cout << "Test " << x << " - " << 4.6 << " = " << x - 4.6 << std::endl;
  std::cout << "Test " << x << " * " << 3.0 << " = " << x * 3.0 << std::endl;
  std::cout << "Test " << x << " / " << 9.3 << " = " << x / 9.3 << std::endl;

  std::cout << "\n";

  std::cout << "Test " << 9.3 << " + " << x << " = " << 9.3 + x << std::endl;
  std::cout << "Test " << 9.3 << " - " << x << " = " << 9.3 - x << std::endl;
  std::cout << "Test " << 9.3 << " * " << x << " = " << 9.3 * x << std::endl;
  std::cout << "Test " << 9.3 << " / " << x << " = " << 9.3 / x << std::endl;
  
  std::cout << "\n";

  std::cout << "Test " << x << " + " << y << " = " << x + y << std::endl;
  std::cout << "Test " << x << " - " << y << " = " << x - y << std::endl;
  std::cout << "Test " << x << " * " << y << " = " << x * y << std::endl;
  std::cout << "Test " << x << " / " << y << " = " << x / y << std::endl << std::endl;

  Complex z(8);
  std::cout << (z /= Complex(2, 3)) << std::endl;
  Complex p(8);
  std::cout << (p * Complex(2, -3)) / (Complex(2,3) * Complex(2, -3)) << std::endl;
} 
