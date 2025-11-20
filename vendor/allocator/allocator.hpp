#pragma once

#include "result.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>

using byte = uint8_t;

class Allocator
{
  public:
    [[nodiscard]] virtual byte *reserve(size_t bytes) = 0;
};

class FixedHeapAllocator : public Allocator
{
  private:
    size_t m_size = 0;
    size_t m_idx = 0;
    uint8_t *m_buf = nullptr;

  public:
    explicit FixedHeapAllocator() = default;
    [[nodiscard]] Result init(const size_t size);
    [[nodiscard]] byte *reserve(size_t bytes);
    ~FixedHeapAllocator();
};

class StaticAllocator : public Allocator
{
  private:
    size_t m_size = 0;
    size_t m_idx = 0;
    uint8_t *m_buf = 0;

  public:
    explicit StaticAllocator() = default;
    [[nodiscard]] Result init(byte *buf, const size_t size);
    [[nodiscard]] byte *reserve(size_t bytes);
    ~StaticAllocator();
};
