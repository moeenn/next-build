#pragma once

#include "allocator.hpp"
#include <cstring>
#include <functional>

template <typename T> class Vector
{
  private:
    size_t m_capacity = 0;
    size_t m_size = 0;
    uint8_t *m_buf = nullptr;

  public:
    explicit Vector() = default;

    [[nodiscard]] Result init(Allocator &allocator, size_t capacity)
    {
        m_capacity = capacity;
        m_size = 0;
        m_buf = (uint8_t *)allocator.reserve(capacity);
        if (m_buf == nullptr)
        {
            return Result::err;
        }

        return Result::ok;
    }

    [[nodiscard]] Result resize(Allocator &allocator)
    {
        bool shouldResize = m_size >= m_capacity;
        if (!shouldResize)
        {
            return Result::ok;
        }

        size_t newCapacity = m_capacity * 2;
        void *newBuf = allocator.reserve(newCapacity);
        if (newBuf == NULL)
        {
            return Result::err;
        }

        std::memcpy(m_buf, newBuf, m_size);
        m_capacity = newCapacity;
        m_buf = (uint8_t *)newBuf;
        return Result::ok;
    }

    [[nodiscard]] Result push(Allocator &allocator, T data)
    {
        bool shouldResize = m_size >= m_capacity;
        if (shouldResize)
        {
            if (resize(allocator) == Result::err)
            {
                return Result::err;
            }
        }

        m_buf[m_size] = data;
        m_size += sizeof(data);
        return Result::ok;
    }

    void iter(std::function<void(size_t, int)> callback)
    {
        size_t stepSize = sizeof(T);
        size_t i;
        for (i = 0; i < m_size; i += stepSize)
        {
            callback(i / stepSize, m_buf[i]);
        }
    }

    ~Vector()
    {
        m_capacity = 0;
        m_size = 0;
        m_buf = nullptr;
    }
};
