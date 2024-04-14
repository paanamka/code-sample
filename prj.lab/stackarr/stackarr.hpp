#pragma once

#ifndef STACKARR_HPP
#define STACKARR_HPP

#include <initializer_list>
#include <cstdlib>
#include <stdexcept>
#include <memory>
#include <complex/complex.hpp>

class StackArr {
public:
	StackArr() = default;
	StackArr(const StackArr& other);
	StackArr(StackArr&& other) noexcept;
	StackArr(const std::initializer_list<Complex>& list);

	StackArr& operator=(const StackArr& other);
	StackArr& operator=(StackArr&& other) noexcept;
	StackArr& operator=(const std::initializer_list<Complex>& list);

	void Push(const Complex& complex);
	void Pop() noexcept;
	bool IsEmpty() const noexcept;
	const Complex& Top() const;
	Complex& Top();
	void Clear() noexcept;

	~StackArr();

private:
	size_t size_ = 0;
	int32_t capacity_ = 0;
	std::unique_ptr<Complex[]> data_ = nullptr;
	std::ptrdiff_t head_ = -1;
};

#endif
