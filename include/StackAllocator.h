#pragma once

#include "Fwd.h"

#include <cstddef>

class StackAllocator
{
    static constexpr size_t Size = 256;

public:
    StackAllocator() = default;
    ~StackAllocator();

    Node * alloc_node();

    short * alloc_short_arr(size_t size);
    short * realloc_short_arr(size_t size, short * current);

    void free(void * ptr) noexcept;

private:
    void alloc_at(std::byte * ptr, size_t to_alloc);

    size_t alloced_at(void * ptr) const noexcept;
    std::byte * find_size(size_t req_size) noexcept { return find_size_from(req_size, m_buffer); }
    std::byte * find_size_from(size_t req_size, const std::byte * from) noexcept;
private:
    std::byte m_buffer[Size] = { std::byte{0} };
    bool m_used[Size] = { false };
    size_t m_alloced_at[Size] = { 0 };
};