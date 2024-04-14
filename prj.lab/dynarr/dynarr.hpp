#pragma once

#ifndef DYNARR_HPP
#define DYNARR_HPP

#include <memory>


class DynArr {
public:
  DynArr() = default;

  float& operator[](const int32_t index);
  const float& operator[](const int32_t index) const;

  DynArr(const int32_t size);
  DynArr(const DynArr& other);
  DynArr(DynArr&& other) noexcept;
  ~DynArr();

  DynArr& operator=(const DynArr& other);
  DynArr& operator=(DynArr&& other) noexcept;
  void Resize(const int32_t new_size);

  bool Empty() const;
  int32_t Size() const;
  int32_t Size(const DynArr& array);
  int32_t Capacity() const;
  int32_t Capacity(const DynArr& array);

private:
  int32_t size_{ 0 };
  int32_t capacity_{ 0 };
  std::unique_ptr <float[]> data_ = nullptr;
};


#endif