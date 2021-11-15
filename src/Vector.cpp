#include "StackAllocator.h"
#include "Vector.h"

namespace {

size_t into_pow_of_2(size_t val)
{
    val |= val >> 1;
    val |= val >> 2;
    val |= val >> 4;
    val |= val >> 8;
    val |= val >> 16;
    val |= val >> 32;
    return val & ~(val >> 1);
}

} // namespace anonymous

void Vector::push_back(short val)
{
    if (m_size == m_capacity) {
        reserve(m_size + 1);
    }
    m_data[m_size] = val;
    m_size++;
}

void Vector::reserve(size_t new_size)
{
    if (new_size < m_capacity) {
        return;
    }
    auto new_capacity = into_pow_of_2(new_size);
    if (new_capacity != new_size) {
        new_capacity <<= 1;
    }

    if (m_data == nullptr) {
        m_data = m_allocator->alloc_short_arr(new_capacity);
        m_capacity = new_capacity;
        return;
    }

    auto * new_data = m_allocator->realloc_short_arr(new_capacity, m_data);
    if (new_data == m_data) {
        m_capacity = new_capacity;
        return;
    }
    for (auto src = m_data, end = src + m_size, dst = new_data; src != end; ++src, ++dst) {
        *dst = *src;
    }
    m_data = new_data;
    m_capacity = new_capacity;
}
