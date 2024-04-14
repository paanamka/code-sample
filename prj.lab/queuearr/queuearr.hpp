#pragma once

#ifndef	QUEUEARR_QUEUEARR_HPP
#define QUEUEARR_QUEUEARR_HPP

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <memory>
#include <complex/complex.hpp>
#include <fstream>

class QueueArr {
public:
	QueueArr() = default;
	QueueArr(const QueueArr& other);
	QueueArr(QueueArr&& other) noexcept;
	QueueArr(const std::initializer_list <Complex>& list);

	QueueArr& operator=(const QueueArr& other);
	QueueArr& operator=(QueueArr&& other) noexcept;
	QueueArr& operator=(const std::initializer_list <Complex>& list);


	void Push(const Complex& complex);
	void Pop() noexcept;

	const Complex& Top() const;
	Complex& Top();
	const Complex& End() const;
	Complex& End();

	bool IsEmpty() const noexcept;
	void Clear() noexcept;


	~QueueArr();

private:
	std::ptrdiff_t head_ = -1;
	std::ptrdiff_t tail_ = -1;
	std::unique_ptr <Complex[]> data_ = nullptr;
	size_t size_ = 0;
	size_t capacity_ = 0;
};

#endif