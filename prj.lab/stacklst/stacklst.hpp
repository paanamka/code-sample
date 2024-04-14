#pragma once

#ifndef STACKLST_HPP
#define STACKLST_HPP

#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <complex/complex.hpp>

class StackLst {
public:
	StackLst() = default;
	StackLst(const StackLst& other);
	StackLst(StackLst&& other) noexcept;

	StackLst& operator= (const StackLst& other);
	StackLst& operator= (StackLst&& other) noexcept;

	void Push (const Complex& complex);
	void Pop() noexcept;
	bool IsEmpty() const noexcept;
	const Complex& Top() const;
	Complex& Top();
	void Clear() noexcept;

	~StackLst();

private:
	struct Node {
		Complex v;
		Node* next = nullptr;
	};

	Node* head_ = nullptr;
};

#endif