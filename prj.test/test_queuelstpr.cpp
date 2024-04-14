#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <queuelstpr/queuelstpr.hpp>
#include "doctest.h"

TEST_CASE("ctor") {
	QueueLstPr q = { 1.1f };
	CHECK_EQ(q.Top(), 1.1f);
	CHECK_EQ(q.IsEmpty(), false);
	QueueLstPr t(q);
	CHECK_EQ(t.Top(), 1.1f);
}

TEST_CASE("push/pop 1") {
	QueueLstPr q = { 1.1f };
	q.Push(1.2f);
	CHECK_EQ(q.Top(), 1.1f);
	q.Push(1.3f);
	q.Push(1.0f);
	CHECK_EQ(q.Top(), 1.0f);
	q.Push(0.5f);
	CHECK_EQ(q.Top(), 0.5f);
	q.Push(0.6f);
	q.Push(0.7f);
	CHECK_EQ(q.Top(), 0.5f);
	q.Pop();
	CHECK_EQ(q.Top(), 0.6f);
	q.Pop();
	CHECK_EQ(q.Top(), 0.7f);
}

TEST_CASE("push/pop 2") {
	QueueLstPr q = { 5.0f };
	q.Push(2.0f);
	q.Push(8.0f);
	CHECK_EQ(q.Top(), 2.0f);
	q.Push(1.0f);
	q.Push(4.0f);
	q.Push(3.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 2.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 3.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 4.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 5.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 8.0f);
	q.Pop();
	CHECK_EQ(q.IsEmpty(), true);
}

TEST_CASE("push/pop 3") {
	QueueLstPr q;
	q.Push(5.0f);
	CHECK_EQ(q.Top(), 5.0f);
	q.Push(10.0f);
	q.Push(9.0f);
	q.Push(11.0f);
	q.Push(6.0f);
	CHECK_EQ(q.Top(), 5.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 6.0f);
	q.Push(10.5f);
	q.Push(12.0f);
	q.Push(7.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 7.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 9.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 10.0f);
	q.Pop();
	CHECK_EQ(q.Top(), 10.5f);
	q.Pop();
	q.Pop();
	CHECK_EQ(q.Top(), 12.0f);
	q.Push(12.5f);
	q.Pop();
	CHECK_EQ(q.Top(), 12.5f);
	q.Pop();
	q.Pop();
	q.Pop();
	CHECK_THROWS(q.Top());
}

TEST_CASE("clear") {
	QueueLstPr q = { 1.0f, 2.0f, 3.0f };
	CHECK_EQ(q.Top(), 1.0f);
	q.Clear();
	CHECK_EQ(q.IsEmpty(), true);
}

TEST_CASE("copy ctor") {
	QueueLstPr q = {1.0f, 2.0f, 3.0f};
	QueueLstPr t(q);
	CHECK_EQ(t.Top(), 1.0f);
	t.Pop();
	t.Pop();
	CHECK_EQ(t.Top(), 3.0f);
}

TEST_CASE("eq operator") {
	QueueLstPr q = { 1.0f, 2.0f, 3.0f };
	QueueLstPr t = { 4.0f, 5.0f, 6.0f, 7.0f };
	t = q;
	CHECK_EQ(t.Top(), 1.0f);
	t.Pop();
	t.Pop();
	t.Pop();
	CHECK_EQ(t.IsEmpty(), true);
}

// stolen tests 
 
TEST_CASE("generic test 0") {
	QueueLstPr qlp;
	CHECK(qlp.IsEmpty());
	qlp.Push(352131);
	CHECK_FALSE(qlp.IsEmpty());
	qlp.Push(-1313);
	qlp.Push(1815);
	CHECK_FALSE(qlp.IsEmpty());
	CHECK_EQ(qlp.Top(), -1313);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 1815);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 352131);
	qlp.Pop();
	CHECK(qlp.IsEmpty());
}

TEST_CASE("copy_ctor") {
	QueueLstPr qlp{ 352131, -1313, 1815 };
	QueueLstPr qlp_c(qlp);

	CHECK_EQ(qlp.Top(), -1313);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 1815);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 352131);
	qlp.Pop();
	CHECK(qlp.IsEmpty());

	CHECK_EQ(qlp_c.Top(), -1313);
	qlp_c.Pop();
	CHECK_EQ(qlp_c.Top(), 1815);
	qlp_c.Pop();
	CHECK_EQ(qlp_c.Top(), 352131);
	qlp_c.Pop();
	CHECK(qlp_c.IsEmpty());
}

TEST_CASE("copy_ctor 2") {
	QueueLstPr qlp{ 1815, -1313, 352131, 1815, -1313 };
	QueueLstPr qlp_c(qlp);

	CHECK_EQ(-1313, qlp.Top());
	qlp.Pop();
	CHECK_EQ(-1313, qlp.Top());
	qlp.Pop();
	CHECK_EQ(1815, qlp.Top());
	qlp.Pop();
	CHECK_EQ(1815, qlp.Top());
	qlp.Pop();
	CHECK_EQ(352131, qlp.Top());
	qlp.Pop();
	CHECK(qlp.IsEmpty());

	CHECK_EQ(-1313, qlp_c.Top());
	qlp_c.Pop();
	CHECK_EQ(-1313, qlp_c.Top());
	qlp_c.Pop();
	CHECK_EQ(1815, qlp_c.Top());
	qlp_c.Pop();
	CHECK_EQ(1815, qlp_c.Top());
	qlp_c.Pop();
	CHECK_EQ(352131, qlp_c.Top());
	qlp_c.Pop();
	CHECK(qlp_c.IsEmpty());
}

TEST_CASE("eq_ctor") {
	QueueLstPr qlp{ 352131, -1313, 1815 };
	QueueLstPr qlp_e = qlp;

	CHECK_EQ(qlp.Top(), -1313);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 1815);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 352131);
	qlp.Pop();
	CHECK(qlp.IsEmpty());

	CHECK_EQ(qlp_e.Top(), -1313);
	qlp_e.Pop();
	CHECK_EQ(qlp_e.Top(), 1815);
	qlp_e.Pop();
	CHECK_EQ(qlp_e.Top(), 352131);
	qlp_e.Pop();
	CHECK(qlp_e.IsEmpty());
}

TEST_CASE("generic test 2 (chain to right side)") {
	QueueLstPr qlp{ -1313, 1815, 352131 };
	CHECK_EQ(qlp.Top(), -1313);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 1815);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 352131);
	qlp.Pop();
	CHECK(qlp.IsEmpty());
}

TEST_CASE("generic test 3 (chain to left side)") {
	QueueLstPr qlp{ 352131, 1815, -1313 };
	CHECK_EQ(qlp.Top(), -1313);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 1815);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 352131);
	qlp.Pop();
	CHECK(qlp.IsEmpty());
}

TEST_CASE("generic test 4 (same elems)") {
	QueueLstPr qlp{ 352131, 352131, 352131, 1815, 1815 };
	CHECK_EQ(qlp.Top(), 1815);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 1815);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 352131);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 352131);
	qlp.Pop();
	CHECK_EQ(qlp.Top(), 352131);
	qlp.Pop();
	CHECK(qlp.IsEmpty());
}

//stolen tests 2

#include <queuelstpr/queuelstpr.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("queuelstpr") {
	QueueLstPr s;
	s.Push(2.5f);
	CHECK(s.Top() == 2.5f);
	s.Push(1.5f);
	CHECK(s.Top() == 1.5f);
	s.Push(1.2f);
	CHECK(s.Top() == 1.2f);
	s.Push(1.3f);
	s.Push(1.7f);
	QueueLstPr ff(s);
	CHECK(ff.Top() == 1.2f);
	s.Pop();
	CHECK(s.Top() == 1.3f);
	s.Pop();
	CHECK(s.Top() == 1.5f);
	s.Pop();
	CHECK(s.Top() == 1.7f);
	s.Pop();
	CHECK(s.Top() == 2.5f);
	s.Pop();
	CHECK_THROWS(s.Top());
	s.Push(3.4f);
	CHECK(s.Top() == 3.4f);
	s.Pop();
	CHECK_THROWS(s.Top());
	ff.Pop();
	CHECK(ff.Top() == 1.3f);
	ff.Pop();
	CHECK(ff.Top() == 1.5f);
	ff.Pop();
	CHECK(ff.Top() == 1.7f);
	ff.Pop();
	CHECK(ff.Top() == 2.5f);
	ff.Pop();
	ff.Push(1.4f);
	CHECK(ff.Top() == 1.4f);
	ff.Pop();
	CHECK_THROWS(ff.Top());
	ff.Push(30.5f);
	CHECK(ff.Top() == 30.5f);
}

TEST_CASE("ctor copy") {
	QueueLstPr a;
	QueueLstPr b(a);
	CHECK_THROWS(b.Top());
	b.Push(3.5f);
	b.Push(3.1f);
	b.Push(0.9f);
	b.Push(2.1f);
	b.Push(3.5f);
	QueueLstPr c(b);
	CHECK(c.Top() == 0.9f);
	c.Pop();
	CHECK(c.Top() == 2.1f);
}

TEST_CASE("operator=") {
	QueueLstPr a;
	QueueLstPr emp;
	QueueLstPr small;
	small.Push(2.6f);
	small.Push(3.1f);
	small.Push(0.9f);
	a.Push(1.7f);
	a.Push(1.5f);
	a.Push(1.3f);
	a.Push(3.0f);
	a.Push(2.7f);
	a.Push(1.0f);
	a.Push(3.9f);
	a.Push(1.8f); // 1, 1.3, 1.5, 1.7, 1.8, 2.7, 3.0, 3.9
	QueueLstPr b;
	//empte = empty
	b = emp;
	CHECK_THROWS(b.Top());
	CHECK_THROWS(emp.Top());
	//empty = big;
	b = a;
	CHECK(b.Top() == 1.0f);
	b.Pop();
	CHECK(b.Top() == 1.3f);
	b.Pop();
	CHECK(b.Top() == 1.5f);
	b.Pop();
	CHECK(b.Top() == 1.7f);
	b.Pop();
	CHECK(b.Top() == 1.8f);
	b.Pop();
	CHECK(b.Top() == 2.7f);
	b.Pop();
	CHECK(b.Top() == 3.0f);
	b.Pop();
	CHECK(b.Top() == 3.9f);
	b.Pop();
	CHECK_THROWS(b.Top());
	b = a;
	//big = small
	b = small;
	CHECK(b.Top() == 0.9f);
	b.Pop();
	CHECK(b.Top() == 2.6f);
	b.Pop();
	CHECK(b.Top() == 3.1f);
	b.Pop();
	CHECK_THROWS(b.Top());
	b = small;
	//small = big
	b = a;
	CHECK(b.Top() == 1.0f);
	b.Pop();
	CHECK(b.Top() == 1.3f);
	b.Pop();
	CHECK(b.Top() == 1.5f);
	b.Pop();
	CHECK(b.Top() == 1.7f);
	b.Pop();
	CHECK(b.Top() == 1.8f);
	b.Pop();
	CHECK(b.Top() == 2.7f);
	b.Pop();
	CHECK(b.Top() == 3.0f);
	b.Pop();
	CHECK(b.Top() == 3.9f);
	b.Pop();
	CHECK_THROWS(b.Top());
	b = a;
	b = emp;
	CHECK_THROWS(b.Top());
}