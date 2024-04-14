#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <memory>
#include <complex/complex.hpp>
#include "queuearr.hpp"
#include <fstream>

QueueArr::QueueArr(const QueueArr& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		data_ = std::make_unique<Complex[]>(capacity_);

		int counter = 0;

		while (counter < capacity_) {
			data_[counter] = other.data_[counter];
			++counter;
		}

		head_ = other.head_;
		tail_ = other.tail_;
}

QueueArr::QueueArr(QueueArr&& other) noexcept {
	std::swap (data_, other.data_);
	std::swap (capacity_, other.capacity_);
	std::swap (size_, other.size_);
	std::swap (head_, other.head_);
	std::swap (tail_ , other.tail_);
}

QueueArr::QueueArr(const std::initializer_list<Complex>& list) {
	capacity_ = list.size() * 2;
	size_ = list.size();

	if (size_ != 0) {
		data_ = std::make_unique<Complex[]>(capacity_);
		head_ = 0;


		for (Complex element : list) {
			++tail_;
			data_[tail_] = element;
		}
	}
}

QueueArr& QueueArr::operator=(const QueueArr& other) {
	if (this != &other) {

		if (other.size_ != 0) {

			data_.reset();
			capacity_ = other.capacity_;
			size_ = other.size_;
			data_ = std::make_unique<Complex[]>(capacity_);

			int counter = 0;

			while (counter < capacity_) {
				data_[counter] = other.data_[counter];
				++counter;
			}

			head_ = other.head_;
			tail_ = other.tail_;
		}

		else {
			(*this).Clear();
		}
	}
	return *this;
}

QueueArr& QueueArr::operator=(QueueArr&& other) noexcept{
	if (this != &other) {
			capacity_ = other.capacity_;
			size_ = other.size_;
			head_ = other.head_;
			tail_ = other.tail_;
			std::swap(data_, other.data_);
	}
	return *this;
}

QueueArr& QueueArr::operator=(const std::initializer_list <Complex>& list) {
	(*this).Clear();

	capacity_ = list.size() * 2;
	size_ = list.size();

	if (list.size() != 0) {
		data_ = std::make_unique<Complex[]>(capacity_);
		head_ = 0;

		for (Complex element : list) {
			++tail_;
			data_[tail_] = element;
		}
	}
	return *this;
}

void QueueArr::Push(const Complex& complex){
	if ((*this).IsEmpty()) {
	
		data_ = std::make_unique<Complex[]>(8);
		data_[0] = complex;
		head_ = 0;
		tail_ = 0;
		size_ = 1;
		capacity_ = 8;
	}

	else if (size_ < capacity_) {
		tail_ = (tail_ + 1) % capacity_;
		++size_;
		data_[tail_] = complex;
	}

	else {
		
		auto queue = std::make_unique<Complex[]>(capacity_ * 2);

		for (int i = 0; i < capacity_; ++i) {
			queue[i] = data_[(head_ + i) % capacity_];
		}

		std::swap(data_, queue);
		head_ = 0;
		++size_;
		tail_ = size_ - 1;
		data_[tail_] = complex;
		capacity_ *= 2;
	}
}

void QueueArr::Pop() noexcept{
	if (data_ != nullptr) {
		int temp = (head_ + 1) % capacity_;
		data_[0] = Complex(0,0);
		head_ = temp;
		--size_;
	}
}

const Complex& QueueArr::Top() const{
	if ((*this).IsEmpty()) {
		throw std::invalid_argument("top of empty queue");
	}
	else {
		return data_[head_];
	}
}

Complex& QueueArr::Top(){
	if ((*this).IsEmpty()) {
		throw std::invalid_argument("top of empty queue");
	}
	else {
		return data_[head_];
	}

}

const Complex& QueueArr::End() const {
	if ((*this).IsEmpty()) {
		throw std::invalid_argument("end of empty queue");
	}
	else {
		return data_[tail_];
	}
}

Complex& QueueArr::End() {
	if ((*this).IsEmpty()) {
		throw std::invalid_argument("end of empty queue");
	}
	else {
		return data_[tail_];
	}
}

bool QueueArr::IsEmpty() const noexcept{
	return (size_ == 0);
}

void QueueArr::Clear() noexcept{
	data_.reset();
	capacity_ = 0;
	size_ = 0;
	head_ = -1;
	tail_ = -1;
}

QueueArr::~QueueArr() {
	(*this).Clear();
}
