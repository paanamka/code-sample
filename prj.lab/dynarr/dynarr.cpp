#include "dynarr.hpp"
#include <stdexcept>

DynArr::DynArr(const int32_t size) {
	Resize(size);
}

float& DynArr::operator[](const int32_t index) {
	if (index >= size_ || index < 0) {
		throw std::invalid_argument ("wrong index");
	}
	return data_[index];
}

const float& DynArr::operator[](const int32_t index) const {
	if (index >= size_ || index < 0) {
		throw std::invalid_argument("wrong index");
	}
	return data_[index];
}

DynArr::DynArr(const DynArr& other) {
	Resize(other.Size());
	for (int i = 0; i < size_; ++i) {
		(*this)[i] = other[i];
	}
}

DynArr::DynArr(DynArr&& other) noexcept {
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);

}


DynArr::~DynArr() {
	data_.reset();
	size_ = 0;
	capacity_ = 0;
}


DynArr& DynArr::operator=(const DynArr& other) {

	if (data_ != other.data_) {

		Resize(other.Size());

		for (int i = 0; i < size_; ++i) {
			(*this)[i] = other[i];
		}
	}
	return *this;
}

DynArr& DynArr::operator=(DynArr&& other) noexcept {

	if (data_ != other.data_) {
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);

		return *this;
	}
}

void DynArr::Resize(const int32_t new_size) {
	if (new_size <= 0) {
		throw std::invalid_argument("forbidden size");
	}
	if (new_size < size_) {
		size_ = new_size;
	}
	else if (new_size > size_ && new_size <= capacity_) {
		int32_t prev_size = size_;
		size_ = new_size;
		for (int i = prev_size; i < size_; ++i) {
			(*this)[i] = 0;
		}
	}
	else {

		auto new_data = std::make_unique<float[]> (new_size);

		for (int i = 0; i < size_; ++i) {
			new_data [i] = (*this)[i];
		}
		for (int i = size_; i < new_size; ++i) {
			new_data[i] = 0;
		}

		data_.reset();
		std::swap(data_, new_data);
		size_ = new_size;
		capacity_ = new_size;
	}
}

bool DynArr::Empty() const {
	return (size_ == 0);
}

int32_t DynArr::Size() const {
	return size_;
}

int32_t DynArr::Size(const DynArr& array) {
	return array.size_;
}

int32_t DynArr::Capacity() const {
	return capacity_;
}

int32_t DynArr::Capacity(const DynArr& array) {
	return array.capacity_;
}