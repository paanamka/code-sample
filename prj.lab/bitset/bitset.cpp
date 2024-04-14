/*#include <vector>
#include <memory>
#include <stdexcept>
#include "bitset.hpp"


BitSet::BitSet(const BitSet& other) {
	std::vector <uint32_t> data_ (0);
	for (int i = 0; i < other.size_; ++i) {
		data_.at(i) = other.data_.at(i);
	}
	size_ = other.size_;
}

BitSet::BitSet(BitSet&& other) noexcept {
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
} 

BitSet& BitSet::operator=(const BitSet& other) {
	data_.assign(other.data_.cbegin(), other.data_.cend());
	size_ = other.size_;

	return *this;
}

BitSet& BitSet::operator=(BitSet&& other) noexcept{
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
	return *this;
}

int32_t position(int32_t index) {
	int32_t pos = 128;
	for (int i = 0; i < index; ++i) {
		pos /= 2;
	}

	return pos;
}

int32_t BitSet::GetSize() const noexcept {
	return size_;
}

void BitSet::Resize(const int32_t size) {
	if (size < 0) {
		throw std::invalid_argument("negative size");
	}
	if (size % 8 == 0) {
		data_.resize(size / 8);
	}
	else {
		data_.resize(size / 8 + 1);
	}
	size_ = size;
}

bool BitSet::Get(const int32_t index) {
	if (index < 0) {
		throw std::invalid_argument("negative index");
	}
	else if (index >= size_) {
		throw std::invalid_argument("invalid index");
	}
	else {
		int32_t move = 0;
		if (index % 8 == 0) {
			move = index / 8;
		}
		else {
			move = index / 8 + 1;
		}
		int32_t pos = position(index % 8);
		int32_t ans = 0;
		ans = data_.at(move) & pos;
		return (bool(ans));
	}
}

void BitSet::Set(const int32_t index, const bool bit) {
	if (index < 0) {
		throw std::invalid_argument("negative index");
	}
	else if (index >= size_) {

	}
} */