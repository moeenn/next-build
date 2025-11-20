#include "allocator.hpp"

[[nodiscard]] Result FixedHeapAllocator::init(const size_t size)
{
    m_size = size;
    m_idx = 0;
    m_buf = (uint8_t *)std::calloc(size, 1);
    if (m_buf == nullptr)
    {
        return Result::err;
    }

    return Result::ok;
}

FixedHeapAllocator::~FixedHeapAllocator()
{
    m_idx = 0;
    m_size = 0;
    free(m_buf);
    m_buf = nullptr;
}

[[nodiscard]] byte *FixedHeapAllocator::reserve(size_t bytes)
{
    if ((m_idx + bytes) > m_size)
    {
        return nullptr;
    }

    byte *out = &m_buf[m_idx];
    m_idx += bytes;
    return out;
}

[[nodiscard]] Result StaticAllocator::init(byte *buf, const size_t size)
{
    m_size = size;
    m_idx = 0;
    m_buf = buf;
    return Result::ok;
}

StaticAllocator::~StaticAllocator()
{
    m_idx = 0;
    m_size = 0;
    m_buf = nullptr;
}

[[nodiscard]] byte *StaticAllocator::reserve(size_t bytes)
{
    if ((m_idx + bytes) > m_size)
    {
        return nullptr;
    }

    byte *out = &m_buf[m_idx];
    m_idx += bytes;
    return out;
}
