#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <complex/complex.hpp>
#include <queuelst/queuelst.hpp>
#include "doctest.h"

Complex z1(1, 2);
Complex z2(2, 3);
Complex z3(3, 4);
Complex z4(4, 5);
Complex z5(5, 6);
Complex z6(6, 7);
Complex z7(7, 8);
Complex z8(8, 9);

TEST_CASE("copy ctor") {
	QueueLst q;
	CHECK_EQ(q.IsEmpty(), true);
	Complex z(1, 2);
	q.Push(z);
	QueueLst u(q);
	CHECK_EQ(u.Top(), z);
	CHECK_EQ(u.End(), z);
	u.Push(Complex(2, 3));
	u.Push(Complex(3, 4));
	CHECK_EQ(u.Top(), Complex(1, 2));
	CHECK_EQ(u.End(), Complex(3, 4));

	QueueLst x;
	QueueLst y = x;
	CHECK_EQ(y.IsEmpty(), true);
	y.Push(z);
	CHECK_EQ(y.Top(), z);
	CHECK_EQ(y.End(), z);
}

TEST_CASE("eq operator") {
	QueueLst q;
	Complex z(8, 9);
	q.Push(z);
	QueueLst u = q;
	CHECK_EQ(u.Top(), z);
	CHECK_EQ(u.End(), z);
}

TEST_CASE("push") {
	QueueLst q;

	q.Push(Complex(1, 2));
	q.Push(Complex(2, 3));
	q.Push(Complex(3, 4));
	q.Push(Complex(4, 5));
	CHECK_EQ(q.Top(), z1);
	CHECK_EQ(q.End(), z4);
}

TEST_CASE("pop"){
	QueueLst q;
	
	q.Push(Complex(1, 2));
	q.Push(Complex(2, 3));
	q.Push(Complex(3, 4));
	q.Push(Complex(4, 5));
	q.Pop();
	CHECK_EQ(q.Top(), z2);
	q.Pop();
	CHECK_EQ(q.Top(), z3);
}

TEST_CASE("move semantics") {
	QueueLst q;
	q.Push(z4);
	q.Push(z5);
	q.Push(z6);
	QueueLst&& h = std::move(q);
	QueueLst s(h);
	CHECK_EQ(s.End(), z6);
	CHECK_EQ(s.Top(), z4);
	CHECK_EQ(h.IsEmpty(), false);
	
	s.Pop();
	CHECK_EQ(s.End(), z6);
	CHECK_EQ(s.Top(), z5);

	QueueLst t;
	t.Push(z1);
	t = h;
	CHECK_EQ(t.End(), z6);
	h.Push(z2);
	h.Push(z3);
	CHECK_EQ(t.End(), z6);
	h.Clear();
	CHECK_EQ(t.End(), z6);
}