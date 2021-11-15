#pragma once

#include "Fwd.h"

#include <cstddef>

class Vector
{
public:
    Vector(StackAllocator * allocator)
        : m_allocator(allocator)
    {}

    ~Vector() noexcept;

    void push_back(short val);

    /**
     * @brief reserves capacity of minimum power of 2 to fit new_size
     *        does nothing if current capacity fits new_size
     *
     * @param new_size wished size
     */
    void reserve(size_t new_size);

    short & operator[](size_t idx) noexcept { return m_data[idx]; }

    short * begin() noexcept { return m_data; }
    short * end() noexcept { return m_data + m_size; }

    size_t size() const noexcept { return m_size; }
    size_t capacity() const noexcept { return m_capacity; }

private:
    short * m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
    StackAllocator * m_allocator;
};