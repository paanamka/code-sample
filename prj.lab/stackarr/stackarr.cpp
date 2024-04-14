#include <initializer_list>
#include <cstdlib>
#include <stdexcept>
#include <memory>
#include "stackarr.hpp"
#include <complex/complex.hpp>

StackArr::StackArr(const StackArr& other) {
	size_ = other.size_;
	capacity_ = other.capacity_;

	data_ = std::make_unique<Complex[]>(capacity_);
	int counter = 0;

	while (counter < capacity_) {
		data_[counter] = other.data_[counter];
		++counter;
	}

	head_ = size_ - 1;
}

StackArr::StackArr(StackArr&& other) noexcept {
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
	std::swap(head_, other.head_);
	std::swap(capacity_, other.capacity_);
}

StackArr::StackArr(const std::initializer_list<Complex>& list){
	capacity_ = list.size() * 2;
	size_ = list.size();
	data_ = std::make_unique<Complex[]>(capacity_);

	for (Complex element : list) {
		++head_;
		data_[head_] = element;
	}
}

StackArr& StackArr::operator=(const StackArr& other) {
	data_.reset();
	size_ = other.size_;
	capacity_ = other.capacity_;
	data_ = std::make_unique<Complex[]>(capacity_);
	
	int counter = 0;

	while (counter < capacity_) {
		data_[counter] = other.data_[counter];
		++counter;
	}

	head_ = size_ - 1;

	return *this;
}

StackArr& StackArr::operator=(StackArr&& other) noexcept {
	if (this != &other) {
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
		std::swap(head_, other.head_);
	}
	return *this;
}

StackArr& StackArr::operator=(const std::initializer_list <Complex>& list){

	data_.reset();
	capacity_ = list.size() * 2;
	size_ = list.size();
	data_ = std::make_unique<Complex[]>(capacity_);

	for (Complex element : list) {
		++head_;
		data_[head_] = element;
	}

	return *this;
}

void StackArr::Push(const Complex& complex) {

	if (size_ == 0) {
		data_ = std::make_unique<Complex[]>(8);
		data_[0] = complex;
		capacity_ = 8;
		size_ = 1;
	}

	else if (head_ + 1 >= capacity_) {

		auto x = std::make_unique<Complex[]>(capacity_ * 2);
		
		int counter = 0;

		while (counter < capacity_) {
			x[counter] = data_[counter];
			++counter;
		}

		x[size_] = complex;
		++size_;
		capacity_ *= 2;
		std::swap(data_, x);
		
	}
	else {
		data_[size_] = complex;
		++size_;
	}
	
	head_ = size_ - 1;
}

void StackArr::Pop() noexcept {

	if (size_ > 0) {
		auto x = std::make_unique<Complex>(data_[head_]);
		x.reset();
		--size_;
		--head_;
	}
}

bool StackArr::IsEmpty() const noexcept{
	return (size_ == 0);
}

const Complex& StackArr::Top() const {
	if (size_ == 0) {
		throw std::invalid_argument("top of empty stack");
	}
	else {
		return data_[head_];
	}
}

Complex& StackArr::Top() {
	if (size_ == 0) {
		throw std::invalid_argument("top of empty stack");
	}
	else {
		return data_[head_];
	}
}

void StackArr::Clear() noexcept {
	size_ = 0;
	capacity_ = 0;
	data_.reset();
	head_ = -1;
}

StackArr::~StackArr() {
	(*this).Clear();
}
