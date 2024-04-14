#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stackarr/stackarr.hpp>
#include <complex/complex.hpp>
#include "doctest.h"

Complex z1 (1, 2);
Complex z2 (3, 4);
Complex z3 (5, 6);

TEST_CASE("default ctor") {
  StackArr s;
  CHECK_THROWS(s.Top());
}

TEST_CASE("initializer list ctor") {
  StackArr s = { z1, z2, z3 };

  CHECK_EQ(z3, s.Top());
  s.Pop();
  CHECK_EQ(z2, s.Top());
  s.Pop();
  CHECK_EQ(z1, s.Top());

  StackArr q{};
  CHECK_EQ(q.IsEmpty(), true);
  CHECK_THROWS(q.Top());
}

TEST_CASE("copy ctor") {
  StackArr ss = { z1, z2, z3 };
  StackArr s (ss);

  CHECK_EQ(z3, s.Top());
  s.Pop();
  CHECK_EQ(z2, s.Top());
  s.Pop();
  CHECK_EQ(z1, s.Top());
  s.Pop();

  CHECK_EQ(z3, ss.Top());
}

TEST_CASE("eq operator") {
  StackArr ss = { z1, z2, z3 };
  StackArr s = ss;

  CHECK_EQ(z3, s.Top());
  s.Pop();
  CHECK_EQ(z2, s.Top());
  s.Pop();
  CHECK_EQ(z1, s.Top());

  CHECK_EQ(z3, ss.Top());

  StackArr k;
  k.Push(z1);

  k = { z2, z3 };
  CHECK_EQ(k.Top(), z3);
  k.Pop();
  CHECK_EQ(k.Top(), z2);
  k.Pop();
  k.Pop();
  k.Pop();
  CHECK_EQ(k.IsEmpty(), true);
  
  StackArr sss;
  StackArr ssss = sss;
  CHECK_EQ(ssss.IsEmpty(), true);

}

TEST_CASE("is empty") {
  StackArr s;
  CHECK_EQ(s.IsEmpty(), true);

  s.Push(z1);
  CHECK_EQ(z1, s.Top());
  CHECK_EQ(s.IsEmpty(), false);
  s.Pop();
  CHECK_EQ(s.IsEmpty(), true);
  CHECK_THROWS(s.Top());
} 

TEST_CASE("clear") {
  StackArr s;
  s.Push(z1);
  s.Push(z2);
  s.Push(z3);
  s.Clear();
  CHECK_EQ(s.IsEmpty(), true);
  CHECK_THROWS(s.Top());
}

TEST_CASE("push / pop") {
  StackArr s;
  for (int i = 0; i < 100; ++i) {
    s.Push(Complex(1, 2));
    s.Push(Complex(2, 3));
    s.Push(Complex(3, 4));
    s.Push(Complex(4, 5));
  }

  Complex z3{ 3, 4 };
  Complex z4{ 4, 5 };
  CHECK_EQ(s.Top(), z4);
  s.Pop();
  CHECK_EQ(s.Top(), z3);
}
