#pragma once

#include <cstdint>
#include <vector>

class BitSet {
	// битовые операции только для последовательностей одинакового размера
	// нужно делать ресайз пользователю
	// подумать над квадратными скобками на чтение и запись
	// подумать какие могут быть форматы ввода вывода в текстовом и бинарном формате
public:

	BitSet() = default;
	BitSet(const BitSet& other);
	BitSet(BitSet&& other) noexcept;

	BitSet& operator= (const BitSet& other);
	BitSet& operator=(BitSet&& other) noexcept;

	int32_t GetSize() const noexcept;
	void Resize(const int32_t size);
	bool Get(const int32_t index);  //получить нужный бит значит сделать побитовое и с индексом
	void Set(const int32_t index, const bool bit);  // побитовое или с индексом

	void operator&= (const BitSet& other);
	void operator|= (const BitSet& other);
	void operator~ ();
	void operator^= (const BitSet& other);

	void Fill(const bool bit);

	~BitSet() = default;

private:
	int32_t size_ = 0;
	std::vector <uint32_t> data_;
};


BitSet operator& (const BitSet& set1, const BitSet& set2);
BitSet operator| (const BitSet& set1, const BitSet& set2);
BitSet operator^ (const BitSet& set1, const BitSet& set2);
